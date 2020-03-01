#ifndef CHAT_EVENT_HPP
#define CHAT_EVENT_HPP

#include "packet.hpp"
#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square_session.hpp"
#include "square.hpp"
#include <vector>
#include "chat_response_event.hpp"
#include "string_converter.hpp"

class ChatEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		pack.Skip(34);
		uint16_t length = pack.ReadShort();
		std::u16string message = pack.ReadUtf16String(length % 254);

		auto square = session->GetSquare();
		if (square == nullptr) return;
		
		square->SendPacket(ChatResponseEvent{ session->Info()->Nickname(), message }.Compose(session));
	}
};

#endif