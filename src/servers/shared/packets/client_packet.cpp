#include "client_packet.hpp"

ClientPacket::ClientPacket()
	: header{ 0 }
{
}

uint64_t ClientPacket::ReadLong()
{
	uint64_t x =
		(buffer[bufferPosition + 7] << 56) |
		(buffer[bufferPosition + 6] << 48) |
		(buffer[bufferPosition + 5] << 40) |
		(buffer[bufferPosition + 4] << 32) |
		(buffer[bufferPosition + 3] << 24) |
		(buffer[bufferPosition + 2] << 16) |
		(buffer[bufferPosition + 1] << 8) |
		(buffer[bufferPosition]);

	this->bufferPosition += 8;

	return x;
}

uint32_t ClientPacket::ReadInt()
{
	uint32_t x =
		(buffer[bufferPosition + 3] << 24) |
		(buffer[bufferPosition + 2] << 16) |
		(buffer[bufferPosition + 1] << 8) |
		(buffer[bufferPosition]);

	this->bufferPosition += 4;
	
	return x;
}

uint16_t ClientPacket::ReadShort()
{
	uint16_t x =
		(buffer[bufferPosition + 1] << 8) |
		(buffer[bufferPosition]);

	this->bufferPosition += 2;

	return x;
}

uint8_t ClientPacket::ReadByte()
{
	uint8_t x = buffer[bufferPosition];

	this->bufferPosition++;

	return x;
}

bool ClientPacket::ReadFlag()
{
	return static_cast<bool>(ReadByte());
}

void ClientPacket::ReadEmpty(uint32_t amount)
{
	this->bufferPosition += amount;
}

void ClientPacket::SetBufferPosition(uint32_t bufferPosition)
{
	this->bufferPosition = bufferPosition;
}
