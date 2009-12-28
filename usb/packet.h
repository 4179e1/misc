#ifndef _PACKET_H
#define _PACKET_H

struct _setup_packet{
	char	bmRequestType;
	char	bRequest;
	short	wValue;
	short	wIndex;
	short	wLength;
};

/****************************
 * bRequest
 ***************************/
#define GET_STATUS			0x00
#define	CLEAR_FEATURE		0x01
#define SET_FEATURE			0x03
#define	SET_ADDRESS			0x05
#define	GET_DESCRIPTOR		0x06
#define SET_DESCRIPTOR		0x07
#define	GET_CONFIGURATION	0x08
#define	SET_CONFIGURATION	0x09
#define GET_INTERFACE		0x0A
#define SET_INTERFACE		0x11
#define SYNCH_FRAME			0x12


/**********************************
 * 		bmRequestType
 *********************************/
/*    Standard Device Request	*/
#define STD_DEVICE_REQUEST_OUT	0x00	/* host to device *//* 00000000 */
#define STD_DEVICE_REQUEST_IN	0x80	/* device to host *//* 10000000 */

/*   Standard Interface Request	*/
#define STD_INTERFACE_REQUESTS_IN	0x81	/* device to host *//* 10000001 */
#define STD_INTERFACE_REQUESTS_OUT	0x01	/* host to device *//* 00000001 */

/* 	  Standard Endpoint Requests */
#define STD_ENDPOINT_REQUESTS_IN	0x82	/* device to host *//* 10000010 */
#define	STD_ENDPOINT_REQUESTS_OUT	0x02	/* host to device *//* 00000010 */


#endif /* _PACKET_H */
