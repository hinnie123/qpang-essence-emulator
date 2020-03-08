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

		// Check if this person is trading, and if he is, if he's trading with the playerid the client has sent
		if (!trades.count(session->Info()->Id()) || trades[session->Info()->Id()].tradingWith->Info()->Id() != targetPlayerId)
			return;

		LobbySession* target = trades[session->Info()->Id()].tradingWith;
		if (target == nullptr)
			return;

		uint8_t state = pack.ReadByte(); // 100 = add, 101 = remove, 102? not sure
		uint32_t unk = pack.ReadInt();

		std::array<char, 40> cardInfo = pack.ReadArray<char, 40>();

		uint64_t dbItemIndex = *(uint64_t*)(&cardInfo[0]);
		if (trades[session->Info()->Id()].didFinish)
		{
			// Oh man, this faggot, oof. He just tried to do the trade bug: https://www.youtube.com/watch?v=VuCp8gVZ2XU
			// But we canceled it :)
			return;
		}

		if (state == 100)
			trades[session->Info()->Id()].proposedItems.push_back(dbItemIndex);
		else if (state == 101)
		{
			// Removing the item from the vector
			auto pos = std::find(trades[session->Info()->Id()].proposedItems.begin(), trades[session->Info()->Id()].proposedItems.end(), dbItemIndex);
			if (pos != trades[session->Info()->Id()].proposedItems.end())
				trades[session->Info()->Id()].proposedItems.erase(pos);
		}

		// This works only for the client that sends the packet, because it stored the information
		// about the card itself.
		session->Send(TradeAddCardSelfEvent{ targetPlayerId }.Compose(session));
		target->Send(TradeAddCardOtherEvent{ session->Info()->Id(), state, unk, cardInfo }.Compose(target));
	}
};

#endif
