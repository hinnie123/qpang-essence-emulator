#ifndef TRADE_OPEN_MENU_EVENT_HPP
#define TRADE_OPEN_MENU_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class OpenTradeMenuEvent : public LobbyPacketEvent {
public:
	OpenTradeMenuEvent(uint32_t targetPlayerId, uint8_t didAccept) { _targetPlayerId = targetPlayerId; _didAccept = didAccept; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_TRADE_OPEN_MENU>();

		packet.WriteInt(_targetPlayerId);
		packet.WriteByte(_didAccept);

		return packet;
	};
private:
	uint32_t _targetPlayerId;
	uint8_t _didAccept;
};

#endif