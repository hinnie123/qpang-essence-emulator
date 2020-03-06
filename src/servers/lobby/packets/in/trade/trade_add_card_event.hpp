#ifndef TRADE_ADD_CARD_EVENT_HPP
#define TRADE_ADD_CARD_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "trade_add_card_self_event.hpp"
#include "trade_add_card_other_event.hpp"
#include "trade.hpp"

class TradeAddCardEvent : public LobbyPacketEvent {
public:
	TradeAddCardEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t targetPlayerId = pack.ReadInt();
		uint8_t state = pack.ReadByte(); // 100 = add, 101 = remove, 102? not sure
		uint32_t unk = pack.ReadInt();

		std::array<char, 40> cardInfo;
		for (size_t i = 0; i < cardInfo.size(); ++i)
		{
			cardInfo[i] = pack.buffer[i + pack.bufferPosition];
		}

		uint64_t dbItemIndex = pack.ReadLong();
		if (!trades.count(session->Info()->Id()))
		{
			// Doesn't exist yet, add it.
			TradeInfo info{};
			info.proposedItems.push_back(dbItemIndex);
			info.didFinish = false;

			trades.emplace(session->Info()->Id(), info);
		}
		else
		{
			if (trades[session->Info()->Id()].didFinish)
			{
				// Oh man, this faggot, oof. He just tried to do the trade bug: https://www.youtube.com/watch?v=VuCp8gVZ2XU
				// But we canceled it :)
				return;
			}

			// Already exists, just add item to vector.
			trades[session->Info()->Id()].proposedItems.push_back(dbItemIndex);
		}

		// This works only for the client that sends the packet, because it stored the information
		// about the card itself.
		session->Send(TradeAddCardSelfEvent{ targetPlayerId }.Compose(session));

		auto target = session->GetLobby()->FindSession(targetPlayerId);
		if (target != nullptr)
			target->Send(TradeAddCardOtherEvent{ session->Info()->Id(), state, unk, cardInfo }.Compose(target.get()));
	}
};

#endif