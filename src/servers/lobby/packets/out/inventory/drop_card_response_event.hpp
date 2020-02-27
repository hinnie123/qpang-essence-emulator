#ifndef DROP_CARD_RESPONSE_EVENT_HPP
#define DROP_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class DropCardResponseEvent : public LobbyPacketEvent {

public:
	DropCardResponseEvent(uint32_t cardId) { _cardId = cardId; };
	
	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_DROP_CARD_RSP>();

		packet.WriteLong(_cardId);

		return packet;
	};
private:
	uint32_t _cardId;
};

#endif