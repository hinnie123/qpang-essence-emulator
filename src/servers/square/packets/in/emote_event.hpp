#ifndef EMOTE_EVENT
#define EMOTE_EVENT

#include "packet.hpp"
#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square_session.hpp"
#include "square.hpp"
#include <vector>
#include "emote_response_event.hpp"
#include "string_converter.hpp"

class EmoteEvent : public SquarePacketEvent {

public:
	EmoteEvent() : SquarePacketEvent(10) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		uint16_t emote = pack.ReadShort();
		session->GetSquare()->SendPacket(EmoteResponseEvent{ session->Info()->Id(), emote }.Compose(session));
	}
};

#endif