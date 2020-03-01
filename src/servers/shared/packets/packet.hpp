#ifndef _PACKET_H
#define _PACKET_H

//std
#include <cstdint>
#include <cstring>
#include <vector>

//this
#include "opcodes.hpp"


struct PacketHeader
{
	//Full length (this header + payload + crc)
	uint16_t fullLength; //0 
	uint8_t encrypted; //2
	uint8_t unknown_02; //3
};


struct PayloadHeader
{
	//Full length (this header + payload + crc)
	uint16_t length; //0 
	Opcode opcode;
};




#endif //_PACKET_H