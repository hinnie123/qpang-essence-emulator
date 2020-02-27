#include "client_packet.hpp"

ClientPacket::ClientPacket()
	: header{ 0 }
{
}

std::u16string ClientPacket::ReadUtf16String(uint32_t length)
{
	Validate(length * 2 + 2);

	std::u16string string = std::u16string(reinterpret_cast<char16_t*>(buffer.data() + this->bufferPosition), length);

	// 2 0 terminator at the end
	this->bufferPosition += length * 2 + 2;

	return string;
}

uint64_t ClientPacket::ReadLong()
{
	Validate(8);

	uint64_t x;

	memcpy(&x, buffer.data() + bufferPosition, 8);

	this->bufferPosition += 8;

	return x;
}

uint32_t ClientPacket::ReadInt()
{
	Validate(4);

	uint32_t x;

	memcpy(&x, buffer.data() + bufferPosition, 4);

	this->bufferPosition += 4;
	
	return x;
}

uint16_t ClientPacket::ReadShort()
{
	Validate(2);

	uint16_t x;

	memcpy(&x, buffer.data() + bufferPosition, 2);

	this->bufferPosition += 2;

	return x;
}

uint8_t ClientPacket::ReadByte()
{
	Validate(1);

	uint8_t x;
	
	x = buffer[bufferPosition];

	this->bufferPosition++;

	return x;
}

bool ClientPacket::ReadFlag()
{
	return static_cast<bool>(ReadByte());
}

void ClientPacket::Skip(uint32_t amount)
{
	Validate(amount);

	this->bufferPosition += amount;
}

void ClientPacket::SetBufferPosition(uint32_t bufferPosition)
{
	this->bufferPosition = bufferPosition;
}

bool ClientPacket::Validate(uint32_t amount)
{
	if (bufferPosition + amount > buffer.size()) {
		throw ClientPacket::PacketLengthException();
	}

	return true;
}
