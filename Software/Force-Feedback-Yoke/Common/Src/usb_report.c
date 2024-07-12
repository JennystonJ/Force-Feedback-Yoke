/*
 * usb_report.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Jennyston
 */

#include "usb_report.h"
#include <string.h>


void UsbReportInit(UsbReport_t *report, PacketParser_t *parser) {
	report->reportId = 0;

	// Clear report data
	memset(report->data, 0, USB_REPORT_MAX_SIZE);

	report->currentParseIndex = 0;
	//report->endianness = inEndian;
}

void UsbReportLoad(UsbReport_t *report, uint8_t *buffer, uint16_t size) {
	// First index contains report id
	report->reportId = *buffer;

	// Following indices store data
	// Copy to report data
	memcpy(report->data, buffer+1, size-1);

	report->currentParseIndex = 0;
}

uint8_t UsbReportGetReportId(UsbReport_t *report) {
	return report->reportId;
}

int32_t UsbReportParseNextInt(UsbReport_t *report) {
	uint8_t *data = report->data + report->currentParseIndex;
	int32_t value;
	ParseBytesEndian(&value, data, sizeof(int32_t), report->endianness);

	// Increment parse index for next parse
	report->currentParseIndex += sizeof(uint32_t);

	return value;
}

float UsbReportParseNextFloat(UsbReport_t *report) {
	uint8_t *data = report->data + report->currentParseIndex;
	float value;
	ParseBytesEndian(&value, data, sizeof(float), report->endianness);

	// Increment parse index for next parse
	report->currentParseIndex += sizeof(float);

	return value;
}

void ParseBytesEndian(void *dest, uint8_t *source, uint8_t length,
		int endianess) {
	// Parse based on endianess
	switch(endianess) {
		case USB_REPORT_IN_BIG_ENDIAN:
			for(int i = 0; i < length; i++) {
				*((uint8_t *)dest+i) = *(source + length-i-1);
			}
			break;
		case USB_REPORT_IN_LITTLE_ENDIAN:
			for(int i = 0; i < length; i++) {
				*((uint8_t *)dest+i) = *(source+i);
			}
			break;
		default:
			// Invalid condition
			break;
	}
}
