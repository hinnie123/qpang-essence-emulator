#ifndef TRADE_REQUEST_EVENT_HPP
#define TRADE_REQUEST_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "trade_response_event.hpp"
#include "trade_open_menu_event.hpp"
#include "trade.hpp"

class TradeRequestEvent : public LobbyPacketEvent {
	enum Error {
		ALREADY_TRADING = 380,
		DOESNT_WANT_TRADE_OFFERS = 877
	};
public:
	TradeRequestEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t targetPlayerId = pack.ReadInt();
		pack.Skip(4);

		auto target = session->GetLobby()->FindSession(targetPlayerId);
		if (target != nullptr)
		{
			// 1 = true, 2 = false
			uint8_t didAccept = pack.ReadByte();

			if (didAccept == 1)
			{
				if (trades.count(targetPlayerId))
				{
					// This person is already trading, send them error that the person is already trading with someone else.
					session->SendError<Opcode::LOBBY_TRADE_ERROR>(Error::ALREADY_TRADING);
				}
				else
				{
					// Add them to the trades map, so if someone tries to trade with a person that's already trading it will tell them that
					// the person is already trading.
					TradeInfo tradeInfo{ {}, false };
					trades[targetPlayerId] = tradeInfo;
					trades[session->Info()->Id()] = tradeInfo;

					target->Send(LobbyTradeResponseEvent{ session->Info()->Id(), didAccept }.Compose(target.get()));
					target->Send(OpenTradeMenuEvent{ session->Info()->Id(), didAccept }.Compose(target.get()));

					session->Send(LobbyTradeResponseEvent{ targetPlayerId, didAccept }.Compose(session));
					session->Send(OpenTradeMenuEvent{ targetPlayerId, didAccept }.Compose(session));
				}
			}
			else
				target->Send(LobbyTradeResponseEvent{ session->Info()->Id(), didAccept }.Compose(target.get()));
		}
	}
};

#endif