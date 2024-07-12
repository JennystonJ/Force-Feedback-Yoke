/*
 * packet_parser.c
 *
 *  Created on: Nov. 24, 2023
 *      Author: Jennyston
 */

#include "packet_parser.h"

void PacketParserInit(PacketParser_t *packetParser,
		void (*parseFunction)(uint8_t *packet, void *parsedDataOut)) {
	packetParser->parseFunction = parseFunction;
}

void PacketParserParse(PacketParser_t *packetParser, uint8_t *packet,
		void *parsedDataOut) {
	packetParser->parseFunction(packet, parsedDataOut);
}
