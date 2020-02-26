#ifndef SERVER_PACKET_HPP
#define SERVER_PACKET_HPP

#include <array>
#include <iostream>
#include <cstdint>

#include "packet.hpp"

class ServerPacket
{
public:


	ServerPacket(Opcode opcode, size_t length = 0);
	ServerPacket();

	template<typename T>
	void Write(T& data, size_t posInBuffer = 4)
	{
		std::memcpy(buffer.data() + posInBuffer, &data, sizeof(T));
	}

	ServerPacket* WriteUtf8String(std::string string, uint32_t length);
	ServerPacket* WriteUtf16String(std::u16string string, uint32_t length);
	ServerPacket* WriteLong(uint64_t value);
	ServerPacket* WriteInt(uint32_t value);
	ServerPacket* WriteShort(uint16_t value);
	ServerPacket* WriteByte(uint8_t value);
	ServerPacket* WriteFlag(bool value);
	ServerPacket* WriteEmpty(uint32_t amount);

	Opcode GetOpcode();

	PayloadHeader ReadPayloadHeader()
	{
		return *reinterpret_cast<PayloadHeader*>(buffer.data());
	}

	void WritePayloadHeader(const PayloadHeader& header)
	{
		if (buffer.size() < 4)
		{
			buffer.resize(4);
		}
		//*reinterpret_cast<PayloadHeader*>(buffer.data()) = header;
		Write(header, 0);
	}

	template<Opcode Op, typename T>
	static ServerPacket Create()
	{
		ServerPacket packet{ Op, sizeof(T) };
		return packet;
	}

	template<Opcode Op, typename T>
	static ServerPacket Create(const T& data)
	{
		ServerPacket packet{ Op, sizeof(T) };
		packet.Write(data);
		return packet;
	}

	template<Opcode Op>
	static ServerPacket Create()
	{
		ServerPacket packet{ Op };

		return packet;
	}


	template<Opcode Op>
	static ServerPacket CreateErrorPacket(uint16_t errCode)
	{
		ServerPacket packet{ Op, 8 };
		packet.Write(errCode, 8);
		return packet;
	}

	ServerPacket MakeCopy();

	void AppendChecksum();

	Opcode m_opCode;
	PacketHeader header;
	std::vector<char> buffer;
private:
	uint32_t m_bufferPosition;
};

#endif