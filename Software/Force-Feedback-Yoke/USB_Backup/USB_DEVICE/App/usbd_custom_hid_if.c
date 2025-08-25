/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v1.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
typedef struct USBD_CUSTOM_HID_Callbacks {
	void (*OutEvent)(uint8_t *buffer);
	uint8_t *(*GetReport)(uint8_t reportId, uint8_t reportType,
			  uint16_t *reportLength);
} USBD_CUSTOM_HID_Callbacks_t;

static USBD_CUSTOM_HID_Callbacks_t callbacks = { 0 };
/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
		0x06, 0x00, 0xff, // Usage Page(Vendor)
		0x09, 0x01, // USAGE (Vendor)
		0xa1, 0x01, // COLLECTION (Application)

		// ----- Feature Report -----
		0x85, 0x01, // Report ID (1)
		0x09, 0x01, // USAGE (Vendor Usage 1)
		0x15, 0x00, // LOGICAL_MINIMUM (0)
		0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
		0x75, 0x08, // REPORT_SIZE (8)
		0x95, 0x11, // REPORT_COUNT (17)
		0xb1, 0x02, // Feature (Data,Var,Abs)

		// ----- Interrupt IN report (device to host) -----
		0x85, 0x02, // Report ID (2)
		0x09, 0x02, // USAGE (Vendor Usage 2)
		0x15, 0x00, // LOGICAL_MINIMUM (0)
		0x26, 0xff, 0xff, // LOGICAL_MAXIMUM (65535)
		0x75, 0x10, // REPORT_SIZE (16)
		0x95, 0x04, // REPORT_COUNT (4)
		0x81, 0x02, // INPUT (Data,Var,Abs)

		// ----- Interrupt OUT report (host to device) -----
		0x85, 0x03, // Report ID (3)
		0x09, 0x03, // USAGE (Vendor Usage 3)
		0x15, 0x00, // LOGICAL_MINIMUM (0)
		0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
		0x75, 0x08, // REPORT_SIZE (8)
		0x95, 0x0C, // REPORT_COUNT (12)
		0x91, 0x02, // OUTPUT (Data,Var,Abs)

		// ----- Feature Report (Capabilities) -----
		0x85, 0x04, // Report ID (4)
		0x09, 0x01, // USAGE (Vendor Usage 1)
		0x15, 0x00, // LOGICAL_MINIMUM (0)
		0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
		0x75, 0x08, // REPORT_SIZE (8)
		0x95, 0x12, // REPORT_COUNT (18)
		0xb1, 0x03, // Feature (Data,Const,Abs)


//
//		0x85, 0x01, // Report ID (1)
//
//		0x15, 0x00, // LOGICAL_MINIMUM (0)
//		0x26, 0xff, 0x00, // LOGICAL_MAXIMUM (255)
//		0x75, 0x08, // REPORT_SIZE (8)
//		0x95, 0x04, // REPORT_COUNT (4)
//		0x09, 0x01, // USAGE (Undefined)
//		0x81, 0x02, // INPUT (Data,Var,Abs)
//
//		0x95, 0x09, // REPORT_COUNT (9)
//		0x09, 0x01, // USUAGE (Undefined)
//		0x91, 0x02,	// OUTPUT (Data,Var,Abs)
//
//		0x95, 0x01, // REPORT_COUNT (1)
//		0x09, 0x01, // USAGE (Undefined)
//		0xb1, 0x02, // FEATURE (Data,Var,Abs)
//
////		0xb1, 0x02, // FEATURE (Data,Var,Abs)
//
//		0x85, 0x02, // Report ID (2)
//
//		0x95, 0x09, // REPORT_COUNT (9)
//		0x09, 0x01, // USAGE (Undefined)
//		0x91, 0x02, // OUTPUT (Data,Var,Abs)
//
//		0x95, 0x01, // REPORT_COUNT (1)
//		0x09, 0x01, // USAGE (Undefined)
//		0xb1, 0x02, // FEATURE (Data,Var,Abs)
  /* USER CODE END 0 */
  0xc0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t *state);
static uint8_t *CUSTOM_HID_GetReport(uint8_t reportId, uint8_t reportType,
		  uint16_t *ReportLength);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS,
  CUSTOM_HID_GetReport
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t *state)
{
  /* USER CODE BEGIN 6 */

//	// Copy the reception buffer to report_buffer
//	memcpy(report_buffer_rx, state, 64);
//
//	flag_rx = 1;


	callbacks.OutEvent(state);
	return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
static uint8_t *CUSTOM_HID_GetReport(uint8_t reportId, uint8_t reportType,
		  uint16_t *ReportLength) {
	return callbacks.GetReport(reportId, reportType, ReportLength);
}

void CUSTOM_HID_RegisterOutEventCallback(void (*OutEvent)(uint8_t *buffer)) {
	callbacks.OutEvent = OutEvent;
}

void CUSTOM_HID_RegisterGetReportCallback(
		uint8_t *(*GetReport)(uint8_t reportId, uint8_t reportType,
				  uint16_t *ReportLength)) {
	callbacks.GetReport = GetReport;
}
/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
