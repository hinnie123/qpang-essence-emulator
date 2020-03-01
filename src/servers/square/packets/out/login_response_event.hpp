#ifndef LOGIN_RESPONSE_EVENT_HPP
#define LOGIN_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <memory>
#include <vector>
#include <cstdint>
#include "string_converter.hpp"

class LoginResponseEvent : public SquarePacketEvent {

public:
	LoginResponseEvent(std::vector<Square::Ptr> squares) { _squares = squares; };

	ServerPacket Compose(SquareSession* session) override {

		auto packet = ServerPacket::Create<Opcode::SQUARE_LOGIN_RSP>();

		uint32_t size = _squares.size();

		packet.WriteShort(size);
		packet.WriteShort(size);
		packet.WriteShort(size);

		for (size_t i = 0; i < size; i++)
		{
			Square::Ptr square = _squares.at(i);

			packet.WriteEmpty(5);
			packet.WriteInt(square->Id());
			packet.WriteByte(square->MaxCapacity());
			packet.WriteByte(square->List().size());
			packet.WriteByte(square->State());
			packet.WriteUtf16String(StringConverter::Utf8ToUtf16(square->Name()), 16);
			packet.WriteEmpty(33);
		}

		return packet;
	};
private:
	std::vector<Square::Ptr> _squares;
};

#endif