#ifndef TRADE_ADD_CARD_SELF_EVENT_HPP
#define TRADE_ADD_CARD_SELF_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class TradeAddCardSelfEvent : public LobbyPacketEvent {
public:
	TradeAddCardSelfEvent(uint32_t targetPlayerId) { _targetPlayerId = targetPlayerId; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_ADD_CARD_SELF>();
		packet.WriteInt(_targetPlayerId);
		return packet;
	};
private:
	uint32_t _targetPlayerId;
};

#endif