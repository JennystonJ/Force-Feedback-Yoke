/*
 * packet_parser.h
 *
 *  Created on: Nov. 24, 2023
 *      Author: Jennyston
 */

#ifndef PACKET_PARSER_H_
#define PACKET_PARSER_H_

#include <stdint.h>

typedef struct PacketParser {
	void (*parseFunction)(uint8_t *packet, void *parsedDataOut);
} PacketParser_t;

/*
 * Initializes Packet Parser structure.
 * param packetParser: pointer to Packet Parser structure
 * param parseFunction: pointer to function called when parsing packet.
 */
void PacketParserInit(PacketParser_t *packetParser,
		void (*parseFunction)(uint8_t *packet, void *parsedDataOut));

/*
 * Parses and outputs given packet
 * param packetParser: pointer to Packet Parser structure
 * param packet: pointer to packet to parse
 * param parsedDataOut: pointer to location to store parsed data
 */
void PacketParserParse(PacketParser_t *packetParser, uint8_t *packet,
		void *parsedDataOut);

#endif /* PACKET_PARSER_H_ */
