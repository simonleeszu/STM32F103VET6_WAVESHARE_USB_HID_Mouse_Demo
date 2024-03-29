/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processing related to Mass Storage Demo
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
#include "stdio.h"	
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_desc.h"
#include "usb_pwr.h"
//#include "usb_bot.h"
//#include "memory.h"
//#include "mass_mal.h"
#include "usb_prop.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Max_Lun = 1;
uint32_t ProtocolValue;
uint32_t stamachine_dgb_state = 0;

DEVICE Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    Joystick_init,
    Joystick_Reset,
    Joystick_Status_In,
    Joystick_Status_Out,
    Joystick_Data_Setup,
    Joystick_NoData_Setup,
    Joystick_Get_Interface_Setting,
    Joystick_GetDeviceDescriptor,
    Joystick_GetConfigDescriptor,
    Joystick_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
  };
USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Joystick_GetConfiguration,
    Joystick_SetConfiguration,
    Joystick_GetInterface,
    Joystick_SetInterface,
    Joystick_GetStatus,
    Joystick_ClearFeature,
    Joystick_SetEndPointFeature,
    Joystick_SetDeviceFeature,
    Joystick_SetDeviceAddress
};

ONE_DESCRIPTOR Device_Descriptor =
{
    (uint8_t*)Joystick_DeviceDescriptor,
    JOYSTICK_SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR Config_Descriptor =
{
    (uint8_t*)Joystick_ConfigDescriptor,
    JOYSTICK_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR Joystick_Report_Descriptor =
  {
    (uint8_t *)Joystick_ReportDescriptor,
    JOYSTICK_SIZ_REPORT_DESC
  };

ONE_DESCRIPTOR Mouse_Hid_Descriptor =
  {
    (uint8_t*)Joystick_ConfigDescriptor + JOYSTICK_OFF_HID_DESC,
    JOYSTICK_SIZ_HID_DESC
  };

ONE_DESCRIPTOR String_Descriptor[4] =
  {
    {(uint8_t*)Joystick_StringLangID, JOYSTICK_SIZ_STRING_LANGID},
    {(uint8_t*)Joystick_StringVendor, JOYSTICK_SIZ_STRING_VENDOR},
    {(uint8_t*)Joystick_StringProduct, JOYSTICK_SIZ_STRING_PRODUCT},
    {(uint8_t*)Joystick_StringSerial, JOYSTICK_SIZ_STRING_SERIAL}
  };

static void Joystick_init(void)
{
	/* Update the serial number string descriptor with the data from the unique
	ID*/
	Get_SerialNum();
	
	pInformation->Current_Configuration = 0;
	/* Connect the device */
	PowerOn();
	
	/* Perform basic device initialization operations */
	USB_SIL_Init();
	
	bDeviceState = UNCONNECTED;

	printf("Joystick_init, bDeviceState = %d \r\n", bDeviceState);	
}


static void Joystick_Reset(void)
{
	/* Set Joystick_DEVICE as not configured */
	pInformation->Current_Configuration = 0;
	pInformation->Current_Interface = 0;/*the default Interface*/
	
	/* Current Feature initialization */
	pInformation->Current_Feature = Joystick_ConfigDescriptor[7];
	SetBTABLE(BTABLE_ADDRESS);
	/* Initialize Endpoint 0 */
	SetEPType(ENDP0, EP_CONTROL);  //Control Endpoint Type
	SetEPTxStatus(ENDP0, EP_TX_STALL);
	SetEPRxAddr(ENDP0, ENDP0_RXADDR);
	SetEPTxAddr(ENDP0, ENDP0_TXADDR);
	Clear_Status_Out(ENDP0);
	SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
	SetEPRxValid(ENDP0);
	
	/* Initialize Endpoint 1 */
	SetEPType(ENDP1, EP_INTERRUPT);   //interrupt Endpoint Type
	SetEPTxAddr(ENDP1, ENDP1_TXADDR);
	SetEPTxCount(ENDP1, 4);
	SetEPRxStatus(ENDP1, EP_RX_DIS);
	SetEPTxStatus(ENDP1, EP_TX_NAK);
	
	/* Set this device to response on default address */
	SetDeviceAddress(0);

	bDeviceState = ATTACHED;
	printf("Joystick_Reset, bDeviceState = %d \r\n", bDeviceState);

}


static void Joystick_SetConfiguration(void)
{
	DEVICE_INFO *pInfo = &Device_Info;
	
	if (pInfo->Current_Configuration != 0)
	{
	  /* Device configured */
	  bDeviceState = CONFIGURED;
	}

	printf("Joystick_SetConfiguration, bDeviceState = %d \r\n", bDeviceState);
}

static void Joystick_SetDeviceAddress (void)
{
	bDeviceState = ADDRESSED;

	printf("Joystick_SetDeviceAddress, bDeviceState = %d \r\n", bDeviceState);

}

//NULL API
static void Joystick_Status_In (void){}
static void Joystick_Status_Out (void){}


// -------------     Debug  -----------------------------


RESULT Joystick_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);

  CopyRoutine = NULL;

  printf("Joystick_Data_Setup, bDeviceState = %d \r\n", bDeviceState);
  
  if ((RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
      && (pInformation->USBwIndex0 == 0))
  {
    if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
    {
      CopyRoutine = Joystick_GetReportDescriptor;
    }
    else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE)
    {
      CopyRoutine = Joystick_GetHIDDescriptor;
    }

  } /* End of GET_DESCRIPTOR */

  /*** GET_PROTOCOL ***/
  else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
           && RequestNo == GET_PROTOCOL)
  {
    CopyRoutine = Joystick_GetProtocolValue;
  }
  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }
  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);
  return USB_SUCCESS;
}

RESULT Joystick_NoData_Setup(uint8_t RequestNo)
{
	printf("Joystick_NoData_Setup, bDeviceState = %d \r\n", bDeviceState);

  if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
  {
    return Joystick_SetProtocol();
  }

  else
  {
    return USB_UNSUPPORT;
  }
}

RESULT Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{

  printf("Joystick_Get_Interface_Setting, bDeviceState = %d \r\n", bDeviceState);

  if (AlternateSetting > 0)
  {
    return USB_UNSUPPORT;
  }
  else if (Interface > 0)
  {
    return USB_UNSUPPORT;
  }
  return USB_SUCCESS;
}


RESULT Joystick_SetProtocol(void)
{
  uint8_t wValue0 = pInformation->USBwValue0;
  ProtocolValue = wValue0;

  printf("Joystick_SetProtocol, bDeviceState = %d \r\n", bDeviceState);
	
  return USB_SUCCESS;
}

uint8_t *Joystick_GetProtocolValue(uint16_t Length)
{
  printf("Joystick_GetProtocolValue, bDeviceState = %d \r\n", bDeviceState);

  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1;
    return NULL;
  }
  else
  {
    return (uint8_t *)(&ProtocolValue);
  }
}
uint8_t *Joystick_GetDeviceDescriptor(uint16_t Length)
{
	printf("Joystick_GetDeviceDescriptor, bDeviceState = %d \r\n", bDeviceState);

    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}
uint8_t *Joystick_GetConfigDescriptor(uint16_t Length)
{
	printf("Joystick_GetConfigDescriptor, bDeviceState = %d \r\n", bDeviceState);

	return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

uint8_t *Joystick_GetStringDescriptor(uint16_t Length)
{
	uint8_t wValue0 = pInformation->USBwValue0;

	printf("Joystick_GetStringDescriptor, bDeviceState = %d \r\n", bDeviceState);
  
  if (wValue0 > 4)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
  }
}

uint8_t *Joystick_GetReportDescriptor(uint16_t Length)
{
	printf("Joystick_GetReportDescriptor, bDeviceState = %d \r\n", bDeviceState);

	return Standard_GetDescriptorData(Length, &Joystick_Report_Descriptor);
}

uint8_t *Joystick_GetHIDDescriptor(uint16_t Length)
{
	printf("Joystick_GetHIDDescriptor, bDeviceState = %d \r\n", bDeviceState);

  	return Standard_GetDescriptorData(Length, &Mouse_Hid_Descriptor);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
