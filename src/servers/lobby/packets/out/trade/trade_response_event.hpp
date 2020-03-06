#ifndef TRADE_RESPONSE_EVENT_HPP
#define TRADE_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class LobbyTradeResponseEvent : public LobbyPacketEvent {
public:
	LobbyTradeResponseEvent(uint32_t targetPlayerId, uint8_t didAccept) { _targetPlayerId = targetPlayerId; _didAccept = didAccept; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_REQUEST_RSP>();

		packet.WriteInt(_targetPlayerId);
		packet.WriteByte(_didAccept);

		return packet;
	};
private:
	uint32_t _targetPlayerId;
	uint8_t _didAccept;
};

#endif