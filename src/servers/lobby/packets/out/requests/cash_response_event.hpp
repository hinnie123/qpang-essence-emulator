#ifndef CASH_RESPONSE_EVENT_HPP
#define CASH_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"

class CashResponseEvent : public LobbyPacketEvent {

public:
	CashResponseEvent(uint32_t cash) { _cash = cash;};

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_REQUEST_CASH_RSP>();

		packet.WriteInt(_cash);

		return packet;
	};
private:
	uint32_t _cash;
};

#endif