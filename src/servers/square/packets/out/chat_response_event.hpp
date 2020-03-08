#ifndef CHAT_RESPONSE_EVENT_HPP
#define CHAT_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class ChatResponseEvent : public SquarePacketEvent {

public:
	ChatResponseEvent(std::u16string sender, std::u16string message) { _sender = sender; _message = message; };

	ServerPacket Compose(SquareSession* session) override {

		auto packet = ServerPacket::Create<Opcode::SQUARE_CHAT_RSP>();

		packet.WriteUtf16String(_sender, 16);
		packet.WriteShort(static_cast<uint16_t>(_message.size()));
		packet.WriteUtf16String(_message, 254);

		return packet;
	};
private:
	std::u16string _sender;
	std::u16string _message;
};

#endif