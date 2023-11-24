/*
 * test_usb_report.cpp
 *
 *  Created on: Oct 13, 2023
 *      Author: Jennyston
 */

#include "gtest/gtest.h"
#include "usb_report.h"

TEST(UsbReportTest, UsbReportLittleParseNextIntTest) {
	UsbReport_t report;
	UsbReportInit(&report, USB_REPORT_IN_LITTLE_ENDIAN);

	const int BUFFER_SIZE = 5;
	uint8_t buffer[BUFFER_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05};

	UsbReportLoad(&report, buffer, BUFFER_SIZE);

	int32_t result = UsbReportParseNextInt(&report);

	ASSERT_EQ(result, 0x05040302) << "USB report little endian integer "
			"parsed incorrectly";
}

TEST(UsbReportTest, UsbReportBigParseNextIntTest) {
	UsbReport_t report;
	UsbReportInit(&report, USB_REPORT_IN_BIG_ENDIAN);

	const int BUFFER_SIZE = 5;
	uint8_t buffer[BUFFER_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05};

	UsbReportLoad(&report, buffer, BUFFER_SIZE);

	int32_t result = UsbReportParseNextInt(&report);

	ASSERT_EQ(result, 0x02030405) << "USB report big endian integer "
			"parsed incorrectly";
}

TEST(UsbReportTest, UsbReportParseBytesLittle) {
	const int LENGTH = 4;
	uint8_t buffer[LENGTH] = {0x01, 0x02, 0x03, 0x04};

	int32_t result;
	ParseBytesEndian(&result, buffer, LENGTH, USB_REPORT_IN_LITTLE_ENDIAN);

	ASSERT_EQ(result, 0x04030201);
}

TEST(UsbReportTest, UsbReportParseBytesBig) {
	const int LENGTH = 4;
	uint8_t buffer[LENGTH] = {0x01, 0x02, 0x03, 0x04};

	int32_t result;
	ParseBytesEndian(&result, buffer, LENGTH, USB_REPORT_IN_BIG_ENDIAN);

	ASSERT_EQ(result, 0x01020304);
}
