#include "server_packet.hpp"

ServerPacket::ServerPacket(Opcode opcode, size_t length)
	: header{ 0 }, m_opCode{ opcode }, m_bufferPosition{ 8 }
{

	buffer.resize(length + m_bufferPosition);
	//header.fullLength = static_cast<uint16_t>(length + 8);
}

ServerPacket::ServerPacket()
	: header{ 0 }
{

}

ServerPacket* ServerPacket::WriteUtf8String(std::string string, uint32_t length)
{
	buffer.resize(buffer.size() + length + 1);

	std::memcpy(buffer.data() + m_bufferPosition, string.data(), string.size() + 1);

	m_bufferPosition += length + 1;

	return this;
}

ServerPacket* ServerPacket::WriteUtf16String(std::u16string string, uint32_t length)
{
	buffer.resize(buffer.size() + length * 2 + 2);

	std::memcpy(buffer.data() + m_bufferPosition, string.data(), string.size() > length ? string.size() * 2  + 2 : length * 2 + 2);

	m_bufferPosition += length * 2 + 2;
	
	return this;
}

ServerPacket* ServerPacket::WriteLong(uint64_t value)
{
	buffer.resize(buffer.size() + 8);

	std::memcpy(buffer.data() + m_bufferPosition, &value, 8);

	m_bufferPosition += 8;

	return this;
}

ServerPacket* ServerPacket::WriteInt(uint32_t value)
{
	buffer.resize(buffer.size() + 4);

	std::memcpy(buffer.data() + m_bufferPosition, &value, 4);

	m_bufferPosition += 4;

	return this;
}

ServerPacket* ServerPacket::WriteShort(uint16_t value)
{
	buffer.resize(buffer.size() + 2);

	std::memcpy(buffer.data() + m_bufferPosition, &value, 2);

	m_bufferPosition += 2;

	return this;
}

ServerPacket* ServerPacket::WriteByte(uint8_t value)
{
	buffer.resize(buffer.size() + 1);

	std::memcpy(buffer.data() + m_bufferPosition, &value, 1);

	m_bufferPosition += 1;

	return this;
}

ServerPacket* ServerPacket::WriteFlag(bool value)
{
	buffer.resize(buffer.size() + 1);

	std::memcpy(buffer.data() + m_bufferPosition, &value, 1);

	m_bufferPosition += 1;

	return this;
}

ServerPacket* ServerPacket::WriteEmpty(uint32_t amount, uint8_t val)
{
	buffer.resize(buffer.size() + amount, val);

	m_bufferPosition += amount;

	return this;
}

Opcode ServerPacket::GetOpcode()
{
	return m_opCode;
}


void ServerPacket::AppendChecksum()
{
	static std::array<uint8_t, 8> checksumBytes = { 0x9C, 0x14, 0xED, 0x29, 0xF2, 0xB5, 0x83, 0x7A };

	uint16_t extra = (buffer.size() + 2) & 7;
	if (!extra)
	{
		return;
	}

	if (extra == 8)
	{
		std::cout << "extra = " << extra << "\n";
		return;
	}

	uint16_t amount = 8 - extra;
	//buffer.resize(buffer.size() + amount + 2);
	for (uint16_t i{ 0 }; i < amount; ++i)
	{
		buffer.push_back(buffer[i] ^ checksumBytes[i]);
	}

	buffer.push_back(static_cast<uint8_t>(amount & 0xFF));
	buffer.push_back(static_cast<uint8_t>((amount >> 8) & 0xFF));
}

ServerPacket ServerPacket::MakeCopy()
{
	ServerPacket packet{};
	packet.header = header;
	packet.buffer = buffer;
	return packet;
}