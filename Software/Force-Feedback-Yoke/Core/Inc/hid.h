/*
 * hid.h
 *
 *  Created on: Aug 21, 2025
 *      Author: Jennyston
 */

#ifndef INC_HID_H_
#define INC_HID_H_

#include <usb_device.h>
#include <stdbool.h>

#define HID_CONTROL_REPORT_ID 1
#define HID_IN_REPORT_ID 2
#define HID_OUT_REPORT_ID 3
#define HID_CAPABILITIES_REPORT_ID 4

void HID_Init(USBD_HandleTypeDef *husbd);
void HID_RegisterReceiveCallback(void (*HIDReceive)(USBD_HandleTypeDef *husbd));
uint8_t *HID_ReadControlBuffer(void);
void HID_SetControlBuffer(uint8_t *controlBuffer);
void HID_SetCapabilitiesBuffer(uint8_t *capabilitesBuffer);
uint8_t *HID_ReadReceiveBuffer(void);
bool HID_GetDataReady(void);
bool HID_GetReceiveReady(void);
bool HID_GetControlReady(void);
void HID_TransmitData(const uint8_t *buffer, uint8_t len);


#endif /* INC_HID_H_ */
