#include "usb.h"
#include "uhci.h"
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <minix/syslib.h>

#define U_BUFFER_SIZE	1024
PRIVATE char buffer[U_BUFFER_SIZE];

PRIVATE int device_caller;

/* initial buffer & host controller */
PRIVATE int init (void) {
	int i;

	/* initial usb device */
	for (i = 0; i < U_BUFFER_SIZE; i++) {
		buffer[i] = '\0';
	}
#if 1
	if(init_hc_drv() == EIO){
		printf("could't find UHCI!\n");
		return (-1);
	}
#endif

	return (OK);

}

PRIVATE void clean_up (void) {

	/* clean up usb device */
}

PRIVATE int u_open (message *m_ptr) {
	int r;

	printf ("U_OPEN\n");
	/* do something to open device */
	
	return (OK);
}

PRIVATE int u_close (message *m_ptr) {
	int r;

	printf ("U_CLOSE\n");
	
	/* do something to close device */

	return (OK);
}

PRIVATE int u_ioctl (message *m_ptr) {

	printf ("U_IOCTL\n");
	/* do something to ioctl */

	return (EINVAL);
}

PRIVATE int u_read (message *m_ptr) {
	int r;
	int nr_transfer;
	int position;
	int count;

	/* initial */
	position = m_ptr->POSITION;
	count = m_ptr->COUNT;

#if 0
	/* debug info */
	printf ("U_READ\n");
	printf ("COUNT: %d\n"
			"POSITION: %d\n"
			"ADDRESS: %X\n" 
			"TYPE: %X\n",
			m_ptr->COUNT,
			m_ptr->POSITION,
			m_ptr->ADDRESS,
			m_ptr->m_type);
	/* end of debug info */
#endif

	if (position >= U_BUFFER_SIZE) { 	/* the request position beyond the buffer range, nothing to transfer */
		nr_transfer = 0;
	} else {							/* position is ok */
		if (position + count > U_BUFFER_SIZE) {		/* count beyond the buffer */
			nr_transfer = U_BUFFER_SIZE - position;
		}
	
		/* data transfer */
		if ( OK != (r = sys_datacopy (SELF, (vir_bytes)buffer, m_ptr->IO_ENDPT, (vir_bytes)m_ptr->ADDRESS, nr_transfer)))
			panic("USB","sys_datacopy failed", r);
	}


	/* debug info */
	printf ("BYTES TRANSFERED: %d\n", nr_transfer);
	/* end of debug info */

	return ( nr_transfer );
}

PRIVATE int u_write (message *m_ptr) {
	printf ("U_WRITE\n");

	return (EINVAL);
}

PRIVATE int u_status (message *m_ptr) {

	printf ("U_STATUS\n");

	/* do something to status */

	return (OK);
}

PRIVATE int u_default (message *m_ptr) {

/*
	printf ("U_DEFAULT\n");
	printf ("message type: %x\n", m_ptr->m_type);
*/
	return (EINVAL);

}

/*===========================================================================*
 *				reply					     *
 *===========================================================================*/
FORWARD _PROTOTYPE ( void reply, (int code, int replyee, int process, int status));
PRIVATE void reply(code, replyee, process, status)
int code;
int replyee;
int process;
int status;
{
	message m;

	m.m_type = code;		/* TASK_REPLY or REVIVE */
	m.REP_STATUS = status;	/* result of device operation */
	m.REP_ENDPT = process;	/* which user made the request */

	send(replyee, &m);
}

/*========================================================================*
 *				usb_task				*
 *========================================================================*/
PUBLIC int main()
{
	int r, proc_nr;
	message msg;
	
	printf ("usb task\n");

	if (init() != OK)
		panic ("USB", "init hw fail", -1);

	while (TRUE) {
		if (receive (ANY, &msg) != OK) continue;

		device_caller = msg.m_source;
		proc_nr = msg.IO_ENDPT;

		/* printf ("who call me? : %d\n", device_caller); */
		switch (msg.m_type) {
			case DEV_OPEN:
				r = u_open (&msg);
				break;
			case DEV_CLOSE:
				r = u_close (&msg);
				break;
			case DEV_IOCTL:
				r = u_ioctl (&msg);
				break;
			case DEV_READ:
				r = u_read (&msg);
				break;
			case DEV_WRITE:
				r = u_write (&msg);
				break;
			case DEV_STATUS:
				r = u_status (&msg);
				break;
			default:
				r = u_default (&msg);
				break;
		}


		if (r != EDONTREPLY) {
			msg.m_type = TASK_REPLY;
			msg.REP_ENDPT = proc_nr;

			msg.REP_STATUS = r;
			reply (TASK_REPLY, device_caller, proc_nr, r);
		}
	}

	clean_up();
	
	return 0;
}
