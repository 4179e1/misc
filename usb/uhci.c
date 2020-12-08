#include "uhci.h"
#include "io.h"
#include "packet.h"
#include "descriptors.h"
#include <unistd.h>

#define REG(offset) (uhci.usbba + offset)
#define BUFSIZ 1023

FORWARD _PROTOTYPE(int probe_hw, (void));
FORWARD _PROTOTYPE(void get_usb_pci, (int devind, PCI_DEV *uhci));
FORWARD _PROTOTYPE(void print_usb_pci, (PCI_DEV *uhci));
FORWARD _PROTOTYPE(void get_usb_io, (UHCI_IO *uhci_io));
FORWARD _PROTOTYPE(void reset_frame, (void));
FORWARD _PROTOTYPE(void add_to_frame, (phys_bytes addr));
FORWARD _PROTOTYPE(void device_enum, (void));
FORWARD _PROTOTYPE(int (build_token), (int len, int toggle, int endpoint, int address, int pid));
FORWARD _PROTOTYPE(void hc_run, (void));
FORWARD _PROTOTYPE(void build_td, (int mode, int status, int token, void* buffer, int bufsiz));
FORWARD _PROTOTYPE(void set_sp, (int type, int request, int value, int index, int len));
FORWARD _PROTOTYPE(void configReg, (phys_bytes addr));
FORWARD _PROTOTYPE(void uhciGReset, (void));
FORWARD _PROTOTYPE(void HCReset, (void));
FORWARD _PROTOTYPE(phys_bytes getFladdr, (int* frlist));
FORWARD _PROTOTYPE(phys_bytes getPhysAddr, (void));
FORWARD _PROTOTYPE(void build_qh, (void));
FORWARD _PROTOTYPE(void ctrltransfer, (void));

PRIVATE int devind;
PRIVATE PCI_DEV uhci;
PRIVATE UHCI_IO uhci_io;
PRIVATE struct _setup_packet sp;

PRIVATE unsigned char zeroBuf[1] = 'Z';
PRIVATE unsigned char data_buf[BUFSIZ];

#define FL_BUFFER_SIZE	(FRAME_LIST_SIZE *2)
PRIVATE int frame_list[FL_BUFFER_SIZE];
PRIVATE int frame_num = 0;
PRIVATE int base_index = 0;

/* make sure it can conatain 3 td */

PRIVATE unsigned int td_list[80];
PRIVATE phys_bytes qh_phys_addr;
PRIVATE phys_bytes td_setup_phys_addr;
PRIVATE phys_bytes td_data_phys_addr;
PRIVATE phys_bytes td_status_phys_addr;

PRIVATE phys_bytes qh_base_index;
PRIVATE int td_setup_base_index;
PRIVATE int td_data_base_index;
PRIVATE int td_status_base_index;

/* initial the host controller */
int init_hc_drv(void)
{
	 phys_bytes addr;
	 if(probe_hw() != OK)
    {
        return EIO;
    }
    printf("UHCI FOUND!\n");

#if 1
    printf ("****BEFORE HC RESET:****\n");
    get_usb_pci (devind, &uhci);
    print_usb_pci(&uhci);
    get_usb_io (&uhci_io);
#endif
    /* issue a Host Controller Reset & Gobal Rest*/
    HCReset();
    
    /*uhciGReset();*/
#if 1
    printf ("********AFTER HC RESET:********\n");
    /*get_usb_pci (devind, &uhci);
    print_usb_pci(&uhci);*/
    get_usb_io (&uhci_io);
#endif
    addr = getFladdr(frame_list);    
    configReg(addr);
    reset_frame();

#if 1
    printf ("****UHCI REGERISTERS VALUES AFTER CONFIGURATION:****\n");
    get_usb_pci (devind, &uhci);
    print_usb_pci (&uhci);
    get_usb_io (&uhci_io);

#endif

#if 1
    device_enum();
#endif
    return 0;
}

/* probe the hardware */
PRIVATE int probe_hw(void)
{
    int r;
    u16_t v_id, d_id;

    pci_init();

    printf("==Searching for your device==\n");
    r = pci_first_dev(&devind, &v_id, &d_id);
    if(r == 0)
    {
        printf("pci_first_dev: got nothing\n");
        return EIO;
    }
    while(r > 0)
    {
        if(v_id == VENDOR_ID && d_id == DEVICE_ID)
            break;
        r = pci_next_dev(&devind, &v_id, &d_id);
    }

    if(v_id != VENDOR_ID || d_id != DEVICE_ID)
    {

        return EIO;
    }
    return OK;
}

PRIVATE void set_sp(int type, int request, int value, int index, int len)
{
    sp.bmRequestType = type;
    sp.bRequest = request;
    sp.wValue = value;
    sp.wIndex = index;
    sp.wLength = len;
}
PRIVATE phys_bytes getPhysAddr(void)
{
    phys_bytes addr = 0;    
    /* to make sure td 4bytes alignment */
    if (OK != GET_PHYS_ADDR(td_list, &addr))
        printf ("GET_PHYS_ADDR: sys_umap failed\n");

    qh_phys_addr = addr & ~0xF;
    qh_phys_addr +=  0x10;
    qh_base_index = (qh_phys_addr - addr)/ sizeof(int);
    td_setup_phys_addr  = qh_phys_addr + 0x20;
    td_setup_base_index = qh_base_index + 8;
    td_data_phys_addr = td_setup_phys_addr + 0x20;
    td_data_base_index = td_setup_base_index + 8;
    td_status_phys_addr = td_data_phys_addr + 0x20;
    td_status_base_index = td_data_base_index + 8;
    return qh_phys_addr;  
}

PRIVATE phys_bytes getFladdr(int* frlist) {
		phys_bytes addr;
		phys_bytes frbaseaddr;
    /* to make sure frame list 4kb alignment */
    if (OK != GET_PHYS_ADDR(frame_list, &addr))
        printf ("get(): sys_umap failed\n");

    frbaseaddr = addr & ~0xFFF;
    frbaseaddr += 0x1000;
    base_index = (frbaseaddr - addr) / sizeof(int);
    return frbaseaddr;    
}
/* enum device on the usb bus */
PRIVATE void device_enum(void)
{
    /* TODO: build the rest td and link them to frame list, complete device enum */
    ctrltransfer();
#if 1
    hc_run();
    sleep(1);
#endif

    printf ("*******AFTER HC RUN*******\n");
    get_usb_io (&uhci_io);
    printf ("TD link %8x, status %8x, token %8x, buf %8x\n",
            td_list[td_setup_base_index + TD_LINK], 
            td_list[td_setup_base_index + TD_STATUS],
            td_list[td_setup_base_index + TD_TOKEN], 
            td_list[td_setup_base_index + TD_BUFFER]);

#if 0
    /* the frame reset should be done after hc exec complete,
    however it strangely doesn't complete */
    reset_frame();
#endif

}

PRIVATE void add_to_frame (phys_bytes addr)
{
    frame_list[base_index + frame_num] = (addr & QH_R | QH_T);
    frame_num++;
}

/* clear buffer, reset the FRNUM register */
PRIVATE void reset_frame (void)
{
    int i;
    int bm;

    frame_num = 0;

    bm = (0 & ~QH_OR_TD | TERMINATE);
    for (i = 0; i < FL_BUFFER_SIZE; i++)
    {
        frame_list[i] = bm;
    }
    for (i = 0; i < BUFSIZ; i++)
    {
        data_buf[i] = '\0';
    }
}
/* write the hc usbcmd register */
PRIVATE void hc_run(void)
{
    uhci_io.usbcmd = uhci_io.usbcmd | USBCMD_RS;
    u_outw (REG(USBCMD), uhci_io.usbcmd);
}


PRIVATE int build_token (int len, int toggle, int endpoint, int address, int pid)
{
    return ((len << TOKEN_ML) | (toggle << TOKEN_D) | (endpoint << TOKEN_EP) | (address << TOKEN_DA) | pid);
}

PRIVATE void build_qh (void) {
		td_list[qh_base_index] = 1;	
		td_list[qh_base_index + 1] = td_setup_phys_addr & QH_R | QH_SELECT & ~QH_T;		
}

PRIVATE void build_td (int mode, int status, int token, void *buffer, int bufsiz)
{
    phys_bytes absaddr;
    int index;
    void *buf;

    if (buffer == NULL)
    {
        buf = buffer;
    }
    else
    {
        if(OK != GET_BUF_ADDR(buffer, bufsiz, &absaddr))
        {
            printf("the sys_umap failed on TDbuf!\n");
        }
        buf = (void *)absaddr;
    }

    if (SETUP == mode)
    {
        index = td_setup_base_index;
        td_list[index + TD_LINK] = td_data_phys_addr;
    }
    else if (DATA == mode)
    {
        index = td_data_base_index;
        td_list[index + TD_LINK] = td_status_phys_addr;
    }
    else if (STATUS == mode)
    {
        index = td_status_base_index;
        td_list[index + TD_LINK] = 1;
    }
    else
    {
        printf ("mode error\n");
        return;
    }
    td_list[index + TD_STATUS] = status;
    td_list[index + TD_TOKEN] = token;
    td_list[index + TD_BUFFER] = (int)buf;
    
    printf ("TD link %8x, status %8x, token %8x, buf %8x\n",
    td_list[index + TD_LINK], status, token, buf);
   
}

PRIVATE void ctrltransfer(void) {
		int token, status;
		phys_bytes addr;
    /* build the setup packet */
    set_sp (STD_DEVICE_REQUEST_IN, GET_DESCRIPTOR, DEVICE_DESCRIPTORS_TYPE, 0, 18);
    
		addr = getPhysAddr();
		build_qh();
    /*setup transaction*/
    status = ((3 << STS_C_ERR) | (1 << STS_ACT));
    token = build_token(8, 0, 0, 0, PID_SETUP);
    build_td(SETUP, status, token, &sp, sizeof(sp));
    /*IN transaction  */
     status = ((3 << STS_C_ERR) | (1 << STS_ACT));
    token = build_token(18, 1, 0, 0, PID_IN);
    build_td(DATA, status, token, &sp, BUFSIZ);
    /*status transaction */
    status = ((3 << STS_C_ERR) | (1 << STS_ACT));
    token = build_token(0, 1, 0, 0, PID_OUT);
    build_td(STATUS, status, token, NULL, 0);
		
    add_to_frame(addr);

}


PRIVATE void get_usb_pci (int devind, PCI_DEV *uhci)
{
    uhci->devind = devind;
    uhci->v_id = pci_attr_r16(devind, VID);
    uhci->d_id = pci_attr_r16(devind, DID);
    uhci->pcicmd = pci_attr_r16(devind, PCICMD);
    uhci->pcists = pci_attr_r16(devind, PCISTS);
    uhci->rid = pci_attr_r8(devind, RID);
    uhci->pi = pci_attr_r8(devind, PI);
    uhci->scc = pci_attr_r8(devind, SCC);
    uhci->basec = pci_attr_r8(devind, BASEC);
    uhci->mlt = pci_attr_r8(devind, MLT);
    uhci->hedt = pci_attr_r8(devind, HEDT);
    uhci->usbba = pci_attr_r32(devind, USBBA) & 0xfffffffe;
    uhci->intln = pci_attr_r8(devind, INTLN);
    uhci->intpn = pci_attr_r8(devind, INTPN);
    uhci->sbrnum = pci_attr_r8(devind, SBRNUM);
}

PRIVATE void print_usb_pci (PCI_DEV *uhci)
{
    printf ("----UHCI PCI CONFIGURATION REGISTER----\n");
    printf("DEVIND: %x\t", uhci->devind);
    printf("UHCI Name: %s\n", pci_dev_name(uhci->v_id, uhci->d_id));
    printf ("PCICMD: %x\t", uhci->pcicmd);
    printf ("PCISTS: %X\t", uhci->pcists);
    printf("RID: %x\n",uhci->rid);
    printf ("PI: %x\t", uhci->pi);
    printf ("SCC: %x\t", uhci->scc);
    printf ("BASEC: %x\n", uhci->basec);
    printf ("MLT: %x\t", uhci->mlt);
    printf ("HEDT: %x\t", uhci->hedt);
    printf("USBBA: %x\n", uhci->usbba);
    printf ("INTLN: %x\t", uhci->intln);
    printf ("INTPN: %x\t", uhci->intpn);
    printf("SBRNUM: %x\t", uhci->sbrnum);
    printf ("LEGSUP: %x\n", uhci->legsup);
}

PRIVATE void get_usb_io (UHCI_IO *uhci_io)
{
    printf ("----USB IO REGISTERS----\n");
    printf ("USBCMD: %x\t\t", uhci_io->usbcmd = u_inw(REG(USBCMD)));
    printf ("USBSTS: %x\t", uhci_io->usbsts = u_inw(REG(USBSTS)));
    printf ("USBINTR: %x\t", uhci_io->usbintr = u_inw(REG(USBINTR)));
    printf ("FRNUM: %x\n", uhci_io->frnum = u_inw(REG(FRNUM)));
    printf ("FLBASEADD: %x\t", uhci_io->flbaseadd = u_inl(REG(FLBASEADD)));
    printf ("SOFMOD: %x\t", uhci_io->sofmod = u_inb(REG(SOFMOD)));
    printf ("PORTSC0: %x\t", uhci_io->portsc0 = u_inw(REG(PORTSC0)));
    printf ("PORTSC1: %x\n", uhci_io->portsc1 = u_inw (REG(PORTSC1)));
}


PRIVATE void configReg(phys_bytes addr)
{
    /* set the default values for io regeristers */
    /* USBCMD_SWDBG means after current TD finished, the HC should stop*/
    uhci_io.usbcmd = uhci_io.usbcmd | USBCMD_MAXP | USBCMD_SWDBG & ~USBCMD_RS;
    u_outw (REG(USBCMD), uhci_io.usbcmd);
    sleep(1);
    /* set the default values for pci configuration regeristrers */
    pci_attr_w16 (devind, PCICMD, (uhci.pcicmd | (1 << 2)));

    uhci_io.portsc0 = uhci_io.portsc0 | PORTSC_CSC;
    uhci_io.portsc1 = uhci_io.portsc1 | PORTSC_CSC;
    u_outw (REG(PORTSC0), uhci_io.portsc0);
    u_outw (REG(PORTSC1), uhci_io.portsc1);
    uhci_io.portsc0 = uhci_io.portsc0 | PORTSC_PE;
    uhci_io.portsc1 = uhci_io.portsc1 | PORTSC_PE;
    u_outw (REG(PORTSC0), uhci_io.portsc0);
    u_outw (REG(PORTSC1), uhci_io.portsc1);

    uhci_io.usbintr = uhci_io.usbintr | USBINTR_SPI | USBINTR_IOC | USBINTR_RI | USBINTR_TO;
    u_outw (REG(USBINTR), uhci_io.usbintr);

    /*frame base address and frame number registers*/
    u_outl (REG(FLBASEADD), addr);
    u_outw (REG(FRNUM), (1 << 10));
}

PRIVATE void uhciGReset(void)
{
    uhci_io.usbcmd = uhci_io.usbcmd | USBCMD_GRESET;
    u_outw (REG(USBCMD), uhci_io.usbcmd);
    sleep (1);
}

PRIVATE void HCReset(void)
{
    uhci_io.usbcmd = uhci_io.usbcmd | USBCMD_HCRESET;
    u_outw (REG(USBCMD), uhci_io.usbcmd);
    sleep (1);
}


