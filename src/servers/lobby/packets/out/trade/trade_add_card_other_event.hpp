#ifndef TRADE_ADD_CARD_OTHER_EVENT_HPP
#define TRADE_ADD_CARD_OTHER_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class TradeAddCardOtherEvent : public LobbyPacketEvent {
public:
	TradeAddCardOtherEvent(uint32_t targetPlayerId, uint8_t state, uint32_t unk, std::array<char, 40> cardInfo) { _targetPlayerId = targetPlayerId; _state = state; _unk = unk; _cardInfo = cardInfo; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_ADD_CARD_OTHER>();

		packet.WriteInt(_targetPlayerId);
		packet.WriteInt(_unk);
		packet.WriteByte(_state);
		packet.WriteInt(_unk);
		packet.WriteArray(_cardInfo);

		return packet;
	};
private:
	uint32_t _targetPlayerId;
	uint8_t _state;
	uint32_t _unk;
	std::array<char, 40> _cardInfo;
};

#endif