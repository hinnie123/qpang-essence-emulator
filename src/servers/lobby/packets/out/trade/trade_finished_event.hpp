#ifndef TRADE_FINISHED_EVENT_HPP
#define TRADE_FINISHED_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class TradeFinishedEvent : public LobbyPacketEvent {
public:
	TradeFinishedEvent(uint32_t targetPlayerId) { _targetPlayerId = targetPlayerId; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_FINISHED>();
		packet.WriteInt(_targetPlayerId);
		return packet;
	};
private:
	uint32_t _targetPlayerId;
};

#endif