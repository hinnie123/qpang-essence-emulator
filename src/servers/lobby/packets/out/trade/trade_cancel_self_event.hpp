#ifndef TRADE_CANCEL_SELF_EVENT_HPP
#define TRADE_CANCEL_SELF_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class TradeCancelSelfEvent : public LobbyPacketEvent {
public:
	TradeCancelSelfEvent(uint32_t targetPlayerId, uint8_t state) { _targetPlayerId = targetPlayerId; _state = state; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_CANCEL_SELF>();

		packet.WriteInt(_targetPlayerId);
		packet.WriteByte(_state);

		return packet;
	};
private:
	uint32_t _targetPlayerId;
	uint8_t _state;
};

#endif