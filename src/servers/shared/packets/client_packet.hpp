#ifndef CLIENT_PACKET_HPP
#define CLIENT_PACKET_HPP

#include "packet.hpp"

#include <cstdint>
#include <vector>
#include <exception>

class ClientPacket
{
public:

	//Size: 4
	struct PayloadHeader
	{
		//Length of the payload, including the header
		uint16_t length; //4 
		Opcode opcode; //6
	};

	struct ReadException : public std::exception
	{
		const char* what() const throw ()
		{
			return "Client Packet Read Exception";
		}
	};


	ClientPacket();
	//First 4 bytes of the payload: payload header
	template<typename T>
	T Read(size_t posInBuffer = 4)
	{
		if (buffer.size() >= sizeof(T))
		{
			return *reinterpret_cast<T*>(buffer.data() + posInBuffer);
		}
		return T{};
	}

	PayloadHeader ReadPayloadHeader()
	{
		return Read<PayloadHeader>(0);
	}

	bool Check()
	{
		//basic check for now
		auto payloadHeader = ReadPayloadHeader();
		if (payloadHeader.length != header.fullLength - 4)
		{
			return false;
		}

		return true;
	}

	PacketHeader header;
	std::vector<char> buffer;

};

#endif