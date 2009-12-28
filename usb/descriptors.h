#ifndef _DESCRIPTORS_H
#define _DESCRIPTORS_H

#define USB20	0x0200
#define USB11	0x0110
#define USB10	0x0100

/**********************
 * lsb	bits	 msb
 * 		01234567
 **********************/

/*********************************************
 *          Device_Descriptors
 ********************************************/

#define DEVICE_DESCRIPTOSR_LENGTH	18
#define DEVICE_DESCRIPTORS_TYPE		0x01

typedef struct {
	char	bLength;			/* 0 Size of the Descriptor in Bytes (18 bytes) */
	char	bDescriptorType;	/* 1 Device Descriptor (0x01) */
	short	bcdUSB;				/* 2 USB Specification Number which device complies too. */ /* usb version */
	char	bDeviceClass;		/* 4 Class Code
									 If equal to Zero, each interface specifies it’s own class code
								 	 if equal to 0xFF, the class code is vendor specified.
									 Otherwise field is valid Class Code. */
	char	bDeviceSubClass;	/* 5 Subclass Code (Assigned by USB Org) */
	char	bDeviceProtocol;	/* 6 Protocol Code (Assigned by USB Org) */
	char	bMaxPacketSize;		/* 7 Maximum Packet Size for Zero Endpoint. Valid Sizes are 8, 16, 32, 64 */
	short	idVendor;			/* 8 Vendor ID (Assigned by USB Org) */	
	short	idProduct;			/* 10 Product ID (Assigned by Manufacturer) */
	short	bcdDevice;			/* 12 Device Release Number */
	char	iManufacturer;		/* 14 Index of Manufacturer String Descriptor */
	char	iProduct;			/* 15 Index of Product String Descriptor */
	char	iSerialNumber;		/* 16 Index of Serial Number String Descriptor */
	char	bNumConfigurations;	/* 17 Number of Possible Configurations */
} Device_Descriptor;



/*************************************************
 *          Configuration_Descriptors
 ************************************************/

#define CONFIGURATION_DESCRIPTORS_TYPE	0x02

typedef struct {
	char	bLength;			/* 0 Size of Descriptor in Bytes */
	char	bDescriptorType;	/* 1 Configuration Descriptor (0x02) */
	short	wTotalLength;		/* 2 Total Length of Data Returned */
	char	bNumInterfaces;		/* 4 Number of Interfaces */
	char	bConfigurationValue;/* 5 Value to use as an argument to select this configuration */
	char	iConfiguration;		/* 6 Index of String Descriptor Describing this configuration */
	char	bmAttributes;		/* 7 D7 Bus Powered
									D6 Self Powered
									D5 Remote Wakeup
									D4..0 Reserved (0) */
	char	bMaxPower;			/* 8 Maximum Power Consumption */

} Configuration_Descriptors;


/****************************************
 *         Interface_Descriptors
 ***************************************/

#define INTERFACE_DESCRIPTORS_TYPE	0x04

typedef struct {
	char	bitLength;			/* 0  Size of Descriptor in Bytes */
	char	bDescriptorType;	/* 1 Interface Descriptor (0x04) */
	char	bInterfaceNumber;	/* 2 Number of Interface */
	char	bAlternateSetting;	/* 3 Value used to select alternative setting */
	char	bNumEndpoints;		/* 4 Number of Endpoints used for this interface */
	char	bInterfaceClass;	/* 5 Class Code (Assigned by USB Org) */
	char	bInterfaceSubClass;	/* 6 Subclass Code (Assigned by USB Org) */
	char	bInterfaceProtocol;	/* 7 Protocol Code */
	char	iInterface;			/* 8 Index of String Descriptor Describing this interface */
} Interface_Descriptors;


/***********************************************
 * 			Endpoint_Descriptors
 **********************************************/

#define ENDPOINT_DESCRIPTORS_LENGTH	7
#define ENDPOINT_DESCRIPTORS_TYPE	0x05

typedef struct {
	char	bLength;			/* 0 Size of Descriptor in Bytes (7 bytes) */
	char	bDescriptonType;	/* 1 Endpoint Descriptor (0x05) */
	char	bEndpointAddress;	/* 2 Endpoint Address, Encoded as follows
										0..3b Endpoint Number
										4..6b Reserved. Set to Zero
										7b Direction (Ignored for Control Endpoints)
										0 = Out Endpoint, 1 = In Endpoint */
	char	bmAttributes;		/* 3 Bits 0..1 Transfer Type
										00 = Control
										01 = Isochronous
										10 = Bulk
										11 = Interrupt
									Bits 2..7 are reserved, except Isochronous*/
	short	wMaxPacketSize;		/* 4 Maximum Packet Size this endpoint is capable of sending or receiving */
	char	bInterval;			/* 6 Interval for polling endpoint data transfers. Value in frame counts.\
								   Ignored for Bulk & Control Endpoints. Iso must equal 1 and field may \
								   range from 1 to 255 for interrupt endpoints.*/
} Endpoint_Descriptors;

#endif /* _DESCRIPTORS_H */
