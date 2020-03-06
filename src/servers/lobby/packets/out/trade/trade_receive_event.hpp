#ifndef TRADE_RECEIVE_EVENT_HPP
#define TRADE_RECEIVE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class ReceiveTradeEvent : public LobbyPacketEvent {
public:
	ReceiveTradeEvent(uint32_t senderPlayerId) { _senderPlayerId = senderPlayerId; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_RECEIVE_REQUEST>();

		packet.WriteInt(_senderPlayerId);
		packet.WriteInt(_senderPlayerId);

		return packet;
	};
private:
	uint32_t _senderPlayerId;
};

#endif