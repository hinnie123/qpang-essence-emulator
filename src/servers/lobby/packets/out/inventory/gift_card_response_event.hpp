#ifndef GIFT_CARD_RESPONSE_EVENT_HPP
#define GIFT_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class GiftCardResponseEvent : public LobbyPacketEvent {

public:
	GiftCardResponseEvent(uint64_t cardId) { _cardId = cardId; };
	
	ServerPacket Compose(LobbySession* session) override {
		
		auto packet = ServerPacket::Create<Opcode::LOBBY_GIFT_ITEM_RSP>();

		packet.WriteEmpty(34);
		packet.WriteLong(_cardId);

		return packet;
	};
private:
	uint64_t _cardId;
};

#endif