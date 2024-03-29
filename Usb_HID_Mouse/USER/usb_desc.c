/**
  ******************************************************************************
  * @file    usb_desc.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Descriptors for Mass Storage Device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"


const uint8_t MASS_DeviceDescriptor[MASS_SIZ_DEVICE_DESC] =
  {
    0x12,   /* bLength  */
    0x01,   /* bDescriptorType */
    0x00,   /* bcdUSB, version 2.00 */
    0x02,
    0x00,   /* bDeviceClass : each interface define the device class */
    0x00,   /* bDeviceSubClass */
    0x00,   /* bDeviceProtocol */
    0x40,   /* bMaxPacketSize0 0x40 = 64 */
    0x83,   /* idVendor     (0483) */
    0x04,
    0x20,   /* idProduct */
    0x57,
    0x00,   /* bcdDevice 2.00*/
    0x02,
    1,              /* index of string Manufacturer  */
    /**/
    2,              /* index of string descriptor of product*/
    /* */
    3,              /* */
    /* */
    /* */
    0x01    /*bNumConfigurations */
  };
const uint8_t MASS_ConfigDescriptor[MASS_SIZ_CONFIG_DESC] =
  {

    0x09,   /* bLength: Configuration Descriptor size */
    0x02,   /* bDescriptorType: Configuration */
    MASS_SIZ_CONFIG_DESC,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    /*      Configuration value */
    0x00,   /* iConfiguration: */
    /*      Index of string descriptor */
    /*      describing the configuration */
    0xC0,   /* bmAttributes: */
    /*      Self powered */
    0x32,   /* MaxPower 100 mA */

    /******************** Descriptor of Mass Storage interface ********************/
    /* 09 */
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    /*      Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0x08,   /* bInterfaceClass: MASS STORAGE Class */
    0x06,   /* bInterfaceSubClass : SCSI transparent*/
    0x50,   /* nInterfaceProtocol */
    4,          /* iInterface: */
    /* 18 */
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    0x81,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00,   /*Polling interval in milliseconds */
    /* 25 */
    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    0x02,   /*Endpoint address (OUT, address 2) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00     /*Polling interval in milliseconds*/
    /*32*/
  };
const uint8_t MASS_StringLangID[MASS_SIZ_STRING_LANGID] =
  {
    MASS_SIZ_STRING_LANGID,
    0x03,
    0x09,
    0x04
  }
  ;      /* LangID = 0x0409: U.S. English */
  #if 0
const uint8_t MASS_StringVendor[MASS_SIZ_STRING_VENDOR] =
  {
    MASS_SIZ_STRING_VENDOR, /* Size of manufacturer string */
    0x03,           /* bDescriptorType = String descriptor */
    /* Manufacturer: "YanHua-TECH CO.LTD" */
    'Y', 0, 'a', 0, 'n', 0, 'H', 0, 'u', 0, 'a', 0, '-', 0, 'T', 0,
    'E', 0, 'C', 0, 'H', 0, ' ', 0, 'C', 0, 'O', 0, '.', 0, 'L', 0,
    'T', 0, 'D', 0
  };
#endif
const uint8_t MASS_StringVendor[MASS_SIZ_STRING_VENDOR] =
  {
    MASS_SIZ_STRING_VENDOR, /* Size of manufacturer string */
    0x03,           /* bDescriptorType = String descriptor */
    /* Manufacturer: "YanHua-TECH CO.LTD" */
    'x', 0, 'x', 0, 'x', 0, 'x', 0, 'x', 0, 'a', 0, '-', 0, 'T', 0,
    'E', 0, 'C', 0, 'H', 0, ' ', 0, 'C', 0, 'O', 0, '.', 0, 'L', 0,
    'T', 0, 'D', 0
  };

const uint8_t MASS_StringProduct[MASS_SIZ_STRING_PRODUCT] =
  {
    MASS_SIZ_STRING_PRODUCT,
    0x03,
    /* Product name: "YanHua Mass Storage" */
    '1', 0, '2', 0, '3', 0, '4', 0, '5', 0, '6', 0, 'M', 0, 'a', 0, 's', 0,
    's', 0, ' ', 0, 'S', 0, 't', 0, 'o', 0, 'r', 0, 'a', 0, 'g', 0, 'e', 0

  };

uint8_t MASS_StringSerial[MASS_SIZ_STRING_SERIAL] =
  {
    MASS_SIZ_STRING_SERIAL,
    0x03,
    /* Serial number*/
    //'B', 0, 'T', 0, 'O', 0, 'B', 0, 'D', 0
    'B', 0, 'O', 0, 'O', 0, 'T', 0, 'L', 0,'O', 0,'A',0,'D', 0,'E',0,'D',0
  };
const uint8_t MASS_StringInterface[MASS_SIZ_STRING_INTERFACE] =
  {
    MASS_SIZ_STRING_INTERFACE,
    0x03,
    /* Interface 0: "YH Mass" */
    //'Y', 0, 'H', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0, 's', 0
    'X', 0, 'X', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0, 's', 0
  };
	/* USB Standard Device Descriptor */
	const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC] =
	  {
		0x12,						/*bLength */
		USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
		0x00,						/*bcdUSB */
		0x02,
		0x00,						/*bDeviceClass*/
		0x00,						/*bDeviceSubClass*/
		0x00,						/*bDeviceProtocol*/
		0x40,						/*bMaxPacketSize 64*/
		0x83,						/*idVendor (0x0483)*/
		0x04,
		0x10,						/*idProduct = 0x5710*/
		0x57,
		0x00,						/*bcdDevice rel. 2.00*/
		0x02,
		1,							/*Index of string descriptor describing
													  manufacturer */
		2,							/*Index of string descriptor describing
													 product*/
		3,							/*Index of string descriptor describing the
													 device serial number */
		0x01						/*bNumConfigurations*/
	  }
	  ; /* Joystick_DeviceDescriptor */
	
	
	/* USB Configuration Descriptor */
	/*	 All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
	const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC] =
	  {
		0x09, /* bLength: Configuration Descriptor size */
		USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
		JOYSTICK_SIZ_CONFIG_DESC,
		/* wTotalLength: Bytes returned */
		0x00,
		0x01,		  /*bNumInterfaces: 1 interface*/
		0x01,		  /*bConfigurationValue: Configuration value*/
		0x00,		  /*iConfiguration: Index of string descriptor describing
										 the configuration*/
		0xE0,		  /*bmAttributes: Self powered */
		0x32,		  /*MaxPower 100 mA: this current is used for detecting Vbus*/
	
		/************** Descriptor of Joystick Mouse interface ****************/
		/* 09 */
		0x09,		  /*bLength: Interface Descriptor size*/
		USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
		0x00,		  /*bInterfaceNumber: Number of Interface*/
		0x00,		  /*bAlternateSetting: Alternate setting*/
		0x01,		  /*bNumEndpoints*/
		0x03,		  /*bInterfaceClass: HID*/
		0x01,		  /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
		0x02,		  /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
		0,			  /*iInterface: Index of string descriptor*/
		/******************** Descriptor of Joystick Mouse HID ********************/
		/* 18 */
		0x09,		  /*bLength: HID Descriptor size*/
		HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
		0x00,		  /*bcdHID: HID Class Spec release number*/
		0x01,
		0x00,		  /*bCountryCode: Hardware target country*/
		0x01,		  /*bNumDescriptors: Number of HID class descriptors to follow*/
		0x22,		  /*bDescriptorType*/
		JOYSTICK_SIZ_REPORT_DESC,/*wItemLength: Total length of Report descriptor*/
		0x00,
		/******************** Descriptor of Joystick Mouse endpoint ********************/
		/* 27 */
		0x07,		   /*bLength: Endpoint Descriptor size*/
		USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/
	
		0x81,		   /*bEndpointAddress: Endpoint Address (IN)*/
		0x03,		   /*bmAttributes: Interrupt endpoint*/
		0x04,		   /*wMaxPacketSize: 4 Byte max */
		0x00,
		0x20,		   /*bInterval: Polling Interval (32 ms)*/
		/* 34 */
	  }; /* MOUSE_ConfigDescriptor */

// very import to analyze, by simon...
const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC] = {
		0x05,		   /*Usage Page(Generic Desktop)*/
		0x01,
		0x09,		   /*Usage(Mouse)*/
		0x02,
		0xA1,		   /*Collection(Logical)*/
		0x01,
		0x09,		   /*Usage(Pointer)*/
		0x01,
		/* 8 */
		0xA1,		   /*Collection(Linked)*/
		0x00,
		0x05,		   /*Usage Page(Buttons)*/
		0x09,
		0x19,		   /*Usage Minimum(1)*/
		0x01,
		0x29,		   /*Usage Maximum(3)*/
		0x03,
		/* 16 */
		0x15,		   /*Logical Minimum(0)*/
		0x00,
		0x25,		   /*Logical Maximum(1)*/
		0x01,
		0x95,		   /*Report Count(3)*/
		0x03,
		0x75,		   /*Report Size(1)*/
		0x01,
		/* 24 */
		0x81,		   /*Input(Variable)*/
		0x02,
		0x95,		   /*Report Count(1)*/
		0x01,
		0x75,		   /*Report Size(5)*/
		0x05,
		0x81,		   /*Input(Constant,Array)*/
		0x01,
		/* 32 */
		0x05,		   /*Usage Page(Generic Desktop)*/
		0x01,
		0x09,		   /*Usage(X axis)*/
		0x30,
		0x09,		   /*Usage(Y axis)*/
		0x31,
		0x09,		   /*Usage(Wheel)*/
		0x38,
		/* 40 */
		0x15,		   /*Logical Minimum(-127)*/
		0x81,
		0x25,		   /*Logical Maximum(127)*/
		0x7F,
		0x75,		   /*Report Size(8)*/
		0x08,
		0x95,		   /*Report Count(3)*/
		0x03,
		/* 48 */
		0x81,		   /*Input(Variable, Relative)*/
		0x06,
		0xC0,		   /*End Collection*/
		0x09,
		0x3c,
		0x05,
		0xff,
		0x09,
		/* 56 */
		0x01,
		0x15,
		0x00,
		0x25,
		0x01,
		0x75,
		0x01,
		0x95,
		/* 64 */
		0x02,
		0xb1,
		0x22,
		0x75,
		0x06,
		0x95,
		0x01,
		0xb1,
		/* 72 */
		0x01,
		0xc0
}; /* Joystick_ReportDescriptor */
	
	/* USB String Descriptors (optional) */
	const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID] =
	  {
		JOYSTICK_SIZ_STRING_LANGID,
		USB_STRING_DESCRIPTOR_TYPE,
		0x09,
		0x04
	  }
	  ; /* LangID = 0x0409: U.S. English */
	
	const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR] =
	  {
		JOYSTICK_SIZ_STRING_VENDOR, /* Size of Vendor string */
		USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
		/* Manufacturer: "STMicroelectronics" */
		'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
		'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
		'c', 0, 's', 0
	  };
	
	const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT] =
	  {
		JOYSTICK_SIZ_STRING_PRODUCT,		  /* bLength */
		USB_STRING_DESCRIPTOR_TYPE, 	   /* bDescriptorType */
		'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'J', 0,
		'o', 0, 'y', 0, 's', 0, 't', 0, 'i', 0, 'c', 0, 'k', 0
	  };
	uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL] =
	  {
		JOYSTICK_SIZ_STRING_SERIAL, 		  /* bLength */
		USB_STRING_DESCRIPTOR_TYPE, 	   /* bDescriptorType */
		'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
	  };

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
