#ifndef CLIENT_PACKET_HPP
#define CLIENT_PACKET_HPP

#include "packet.hpp"

#include <cstdint>
#include <vector>
#include <exception>
#include <string>

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

	struct PacketLengthException : public std::exception
	{
		const char* what() const throw ()
		{
			return "Client packet received is too small";
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

	std::u16string ReadUtf16String(uint32_t length);
	uint64_t ReadLong();
	uint32_t ReadInt();
	uint16_t ReadShort();
	uint8_t ReadByte();
	bool ReadFlag();

	template<typename T, uint32_t N>
	std::array<T, N> ReadArray()
	{
		std::array<T, N> arr;
		uint32_t sizeToCopy = sizeof(T) * N;

		std::memcpy(&arr, buffer.data() + bufferPosition, sizeToCopy);
		bufferPosition += sizeToCopy;

		return arr;
	}

	void Skip(uint32_t amount = 1);
	void SetBufferPosition(uint32_t bufferPosition);
	bool Validate(uint32_t amount = 1);

	uint32_t bufferPosition;
	PacketHeader header;
	std::vector<char> buffer;
};

#endif