#ifndef TRADE_EVENT_HPP
#define TRADE_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "trade_receive_event.hpp"

class LobbyTradeEvent : public LobbyPacketEvent {
public:
	LobbyTradeEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t targetPlayerId = pack.ReadInt();

		auto target = session->GetLobby()->FindSession(targetPlayerId);
		if (target != nullptr)
		{
			target->Send(ReceiveTradeEvent{ session->Info()->Id() }.Compose(target.get()));
		}
	}
};

#endif