#ifndef EMOTE_RESPONSE_EVENT_HPP
#define EMOTE_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <cstdint>

class EmoteResponseEvent : public SquarePacketEvent {

public:
	EmoteResponseEvent(uint32_t playerId, uint32_t emoteId) { _playerId = playerId;  _emoteId = emoteId; };

	ServerPacket Compose(SquareSession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::SQUARE_EMOTE_PLAYER>();

		packet.WriteInt(_playerId);
		packet.WriteInt(_emoteId);

		return packet;
	};
private:
	uint32_t _playerId;
	uint32_t _emoteId;
};

#endif