#ifndef SERVER_PACKET_HPP
#define SERVER_PACKET_HPP

#include <array>
#include <iostream>
#include <cstdint>

#include "packet.hpp"

class ServerPacket
{
public:


	ServerPacket(Opcode opcode, size_t length);
	ServerPacket();
	template<typename T>
	void Write(T& data, size_t posInBuffer = 4)
	{
		std::memcpy(buffer.data() + posInBuffer, &data, sizeof(T));
	}


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
	static ServerPacket CreateErrorPacket(uint16_t errCode)
	{
		ServerPacket packet{ Op, 8 };
		packet.Write(errCode, 8);
		return packet;
	}

	ServerPacket MakeCopy();

	void AppendChecksum();

	PacketHeader header;
	std::vector<char> buffer;
};

#endif