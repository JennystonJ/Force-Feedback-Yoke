/*
 * usb_report.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Jennyston
 */

#ifndef USB_REPORT_H_
#define USB_REPORT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define USB_REPORT_IN_LITTLE_ENDIAN 0
#define USB_REPORT_IN_BIG_ENDIAN 1

#define USB_REPORT_MAX_SIZE 64

typedef struct UsbReport {
	uint8_t reportId;
	uint8_t data[USB_REPORT_MAX_SIZE];
	uint16_t currentParseAddr;
	uint8_t endianness;
} UsbReport_t;

/*
 * Initializes USB Report structure
 * param report: pointer to USB report structure
 * param endianness: specifies report input endianness
 */
void UsbReportInit(UsbReport_t *report, uint8_t endianness);

/*
 * Loads report into memory for further processing
 * param report: pointer to USB report structure (stores report)
 * param buffer: pointer to report buffer to copy from
 * param size: number of bytes to copy from report buffer
 */
void UsbReportLoad(UsbReport_t *report, uint8_t *buffer, uint16_t size);

/*
 * Process the next 4 bytes as an integer
 * param report: pointer to USB report structure
 */
int32_t UsbReportParseNextInt(UsbReport_t *report);

/*
 * Process the next 4 bytes as a 32-bit floating point
 * param report: pointer to USB report structure
 */
float UsbReportParseNextFloat(UsbReport_t *report);

//TODO: Move to separate C file
/*
 * Parse bytes based on endianess
 * param dest: pointer to destination of parsed bytes
 * param source: pointer to source of bytes to be parsed
 * param length: number of bytes to be parsed
 * param endianess: input endianess
 */
void ParseBytesEndian(void *dest, uint8_t *source, uint8_t length,
		int endianess);

#ifdef __cplusplus
}
#endif

#endif /* USB_REPORT_H_ */
