#ifndef __MINUX_UHCI_H
#define __MINUX_UHCI_H

#include <sys/types.h>
#include "../drivers.h"
#include "../../include/ibm/pci.h"

#define SET_BIT(var, n)  (var = (var | (1 << n)))
#define UNSET_BIT(var, n) (var =(var &~ (1 << n)))
#define IS_BIT_SET(var, n) (var & (1 << n))

/*===========================================
 * Refer to intel 82371 datasheet *
 * ========================================*/

#define VENDOR_ID 	0x8086
#define DEVICE_ID 	0x7112


_PROTOTYPE(int init_hc_drv, (void)); 

/* PCI Configuration Registers(USB-D29:F0/F1/F2/F3)*/
/*		name		offset			details			*/
#define VID			0x00	/* 00-01h */
#define DID			0x02	/* 02-03h */
#define PCICMD		0x04	/* 04-05h */
#define PCISTS		0x06	/* 06-07h */
#define RID			0x08	/* 08h */
#define CLASSC		0x09	/* 09-0Bh */
#define PI			0x09
#define SCC			0x0A
#define BASEC		0x0B
#define MLT			0x0D	/* 0Dh */
#define	HEDT		0x0E	/* 0Eh */
#define USBBA		0x20	/* 20-23h */
#define INTLN		0x3C	/* 3Ch */
#define INTPN		0x3D	/* 3Dh */
#define SBRNUM		0x60	/* 60h */
#define LEGSUP		0xC0	/* C0-C1h */


/*NOTE:These registers are WORD writable only. Byte writes to these registers have unpredictable effects.*/

typedef struct _pci_dev {
	u32_t	devind;		/*minix pci device id, for pci configuration space*/
	u16_t	v_id;		/*vendor id*/
	u16_t	d_id;		/*device id*/
	short	pcicmd;
	short	pcists;
	char	rid;		/* vesion of the device */
	char	pi;
	char	scc;
	char	basec;
	char	mlt;
	char	hedt;
	u32_t	usbba;		/* USB IO Space Base Address */
	char	intln;
	char	intpn;
	char	sbrnum; 	/* Serial Bus Release Number */
	short	legsup;
}PCI_DEV;


/* USB I/O Registers*/
/*		name		offset			details			*/
#define USBCMD		0x00	/* 00-01h */	
#define USBSTS		0x02	/* 02-03h */
#define USBINTR		0x04	/* 04-05h */
#define FRNUM		0x06	/* 06-07h */
#define FLBASEADD	0x08	/* 08-0Bh */
#define SOFMOD		0x0C	/* 0Ch */
#define PORTSC0		0x10	/* 10-11h */
#define PORTSC1		0x12	/* 12-13h */

typedef struct _uhci_io {
	short	usbcmd;		/* USB COMMAND REGISTER */
	short	usbsts;		/* USB STATUS REGISTER */
	short	usbintr;	/* USB INTERRUPT ENABLE REGISTER */
	short	frnum;		/* FRAME NUMBER REGISTER */
	int		flbaseadd;	/* FRAME LIST BASE ADDRESS REGISTER */
	char	sofmod;		/* START OF FRAME (SOF) MODIFY REGISTER */
	short	portsc0;	/* PORT STATUS AND CONTROL REGISTER 0 */
	short	portsc1;	/* PORT STATUS AND CONTROL REGISTER 1 */
} UHCI_IO;

/* bitmap for uhci */
/* USBCMD */
#define USBCMD_MAXP		(1 << 7)		/* 1=64 bytes. 0=32 bytes */
#define USBCMD_CF		(1 << 6)		/* Config Flag (sw only) */
#define	USBCMD_SWDBG	(1 << 5)		/* 1=Debug mode. 0=Normal Mode */
#define	USBCMD_FGR		(1 << 4)		/* Force Global Resume */
#define	USBCMD_EGSM		(1 << 3)		/* SW Debug mode */
#define USBCMD_GRESET	(1 << 2)	/* Global reset */
#define USBCMD_HCRESET	(1 << 1)		/* Host reset */
#define	USBCMD_RS		(1 << 0)		/* 1=Run. 0=Stop */

#define USBSTS_RESET	0xffffffff
/* USBSTS */
#define USBSTS_HCH		(1 << 5)		/* HC Halted */
#define USBSTS_HCPE		(1 << 4)		/* Host Controller Process Error:the schedule is buggy */
#define USBSTS_HSE		(1 << 3)		/* Host System Error: PCI problems */
#define	USBSTS_RD		(1 << 2)		/* Resume Detect */
#define USBSTS_UEI		(1 << 1)		/* Interrupt due to error */
#define	USBSTS_USBINT	(1 << 0)		/* Interrupt due to IOC */

/* USBINTR */
#define USBINTR_SPI		(1 << 3)	/* 1=Enabled. 0=Disabled. */
#define USBINTR_IOC		(1 << 2)	/* 1=Enabled. 0=Disabled. */
#define USBINTR_RI		(1 << 1)	/* 1=Enabled. 0=Disabled. */
#define USBINTR_TO		(1 << 0)	/* 1=Enabled. 0=Disabled. */
#define USBINTR_CRCI	(1 << 0)	/* 1=Enabled. 0=Disabled. */

/* PORTSC */
#define PORTSC_SSP		(1 << 12)
#define PORTSC_OCIC		(1 << 11)
#define PORTSC_OCI		(1 << 10)	/* RO */
#define PORTSC_PRST		(1 << 9)	/* 1=Port is in Reset. 0=Port is not in Reset */
#define PORTSC_LSDA		(1 << 8)	/* RO */
#define PORTSC_RD		(1 << 6)
#define PORTSC_PEC		(1 << 3)
#define PORTSC_PE		(1 << 2)
#define PORTSC_CSC		(1 << 1)
#define PORTSC_CCS		(1 << 0)


#define FRAME_LIST_SIZE 1024
#define FL_RESERVED		0xc
#define QH_OR_TD		(1 << 1)
#define TERMINATE		(1 << 0)

#define SETUP	0
#define DATA	1
#define STATUS	2

struct _td {
	/* Hardware fields */
	u32_t link;
	u32_t status;	
	u32_t token;
	void* buffer;
	/* Software fields */
	u32_t absaddr;
	struct _td *next;
	int fill1;
	int fill2;
};
#define TD_LINK		0
#define TD_STATUS	1
#define TD_TOKEN	2
#define	TD_BUFFER	3
#define TD_ABSADDR	5

struct _qh {
	/* Hardware fields */
	u32_t link;
	u32_t element;
	/* Software fields */
};

#define QH_R		  ~(1 << 3 | 1 << 2)
#define QH_SELECT (1 << 1)
#define QH_T			(1 << 0)

#define TD_R			~(1 << 3)
#define TD_VF			(1 << 2)
#define TD_QH			(1 << 1)
#define TD_T			(1 << 0)

#define TOKEN_ML	21
#define TOKEN_D		19
#define TOKEN_EP	15
#define TOKEN_DA	8

#define STS_C_ERR	27
#define STS_ACT		23

/*PID*/
#define PID_UNDEF_0		0xf0
#define PID_OUT				0xe1
#define PID_ACK				0xd2
#define PID_DATA0			0xc3
#define PID_PING			0xb4	/* USB 2.0 */
#define PID_SOF				0xa5
#define PID_NYET			0x96	/* USB 2.0 */
#define PID_DATA2			0x87	/* USB 2.0 */
#define PID_SPLIT			0x78	/* USB 2.0 */
#define PID_IN				0x69
#define PID_NAK				0x5a
#define PID_DATA1			0x4b
#define PID_PREAMBLE	0x3c	/* Token mode */
#define PID_ERR				0x3c	/* USB 2.0: handshake mode */
#define PID_SETUP			0x2d
#define PID_STALL			0x1e
#define PID_MDATA			0x0f	/* USB 2.0 */


/*
 *	Transfer Descriptors
 */

/*
 * for TD <status>:
 */
 
 /* Short Packet Detect  1 means the packet is a input packet, it 
 	* is in a queue, and it is sucessfully completes with an actul 
 	* length less then the maximum length
 	*/
#define TD_CTRL_SPD		(1 << 29)	

/* Error Counter bits, 11 -> 3 error,10 -> 2, 01 -> 1 error*/	
#define TD_CTRL_C_ERR_MASK	(3 << 27)
#define TD_CTRL_C_ERR_SHIFT	27

#define TD_CTRL_LS		(1 << 26)	/* Low Speed Device */
#define TD_CTRL_IOS		(1 << 25)	/* Isochronous Select */
#define TD_CTRL_IOC		(1 << 24)	/* Interrupt on Complete */
#define TD_CTRL_ACTIVE		(1 << 23)	/* TD Active */
#define TD_CTRL_STALLED		(1 << 22)	/* TD Stalled */
#define TD_CTRL_DBUFERR		(1 << 21)	/* Data Buffer Error */
#define TD_CTRL_BABBLE		(1 << 20)	/* Babble Detected */
#define TD_CTRL_NAK		(1 << 19)	/* NAK Received */
#define TD_CTRL_CRCTIMEO	(1 << 18)	/* CRC/Time Out Error */
#define TD_CTRL_BITSTUFF	(1 << 17)	/* Bit Stuff Error */
#define TD_CTRL_ACTLEN_MASK	0x7FF	/* actual length, encoded as n - 1 */

#define TD_CTRL_ANY_ERROR	(TD_CTRL_STALLED | TD_CTRL_DBUFERR | \
				 TD_CTRL_BABBLE | TD_CTRL_CRCTIMEO | \
				 TD_CTRL_BITSTUFF)

#define uhci_maxerr(err)		((err) << TD_CTRL_C_ERR_SHIFT)
#define uhci_status_bits(ctrl_sts)	((ctrl_sts) & 0xF60000)
#define uhci_actual_length(ctrl_sts)	(((ctrl_sts) + 1) & \
			TD_CTRL_ACTLEN_MASK)	/* 1-based */

/*
 * for TD <info>: (a.k.a. Token)
 */
/*#define td_token(td)		le32_to_cpu((td)->token) */

#define TD_TOKEN_DEVADDR_SHIFT	8
#define TD_TOKEN_TOGGLE_SHIFT	19
#define TD_TOKEN_TOGGLE		(1 << 19)
#define TD_TOKEN_EXPLEN_SHIFT	21
#define TD_TOKEN_EXPLEN_MASK	0x7FF	/* expected length, encoded as n-1 */
#define TD_TOKEN_PID_MASK	0xFF

#define uhci_explen(len)	((((len) - 1) & TD_TOKEN_EXPLEN_MASK) << \
					TD_TOKEN_EXPLEN_SHIFT)

#define uhci_expected_length(token) ((((token) >> TD_TOKEN_EXPLEN_SHIFT) + \
					1) & TD_TOKEN_EXPLEN_MASK)
#define uhci_toggle(token)	(((token) >> TD_TOKEN_TOGGLE_SHIFT) & 1)
#define uhci_endpoint(token)	(((token) >> 15) & 0xf)
#define uhci_devaddr(token)	(((token) >> TD_TOKEN_DEVADDR_SHIFT) & 0x7f)
#define uhci_devep(token)	(((token) >> TD_TOKEN_DEVADDR_SHIFT) & 0x7ff)
#define uhci_packetid(token)	((token) & TD_TOKEN_PID_MASK)
#define uhci_packetout(token)	(uhci_packetid(token) != USB_PID_IN)
#define uhci_packetin(token)	(uhci_packetid(token) == USB_PID_IN)

#define GET_PHYS_ADDR(TDLIST, ADDR)\
sys_umap(SELF, D, ((vir_bytes)TDLIST), (phys_bytes)(sizeof(TDLIST)), (ADDR))
 
#define GET_BUF_ADDR(BUFFER, SIZ, ADDR) \
sys_umap(SELF, D, ((vir_bytes)BUFFER), (phys_bytes)(SIZ), (ADDR))
#endif
