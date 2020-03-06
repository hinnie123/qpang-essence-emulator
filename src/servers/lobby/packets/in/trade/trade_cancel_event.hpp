#ifndef TRADE_CANCEL_EVENT_HPP
#define TRADE_CANCEL_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "trade_cancel_self_event.hpp"
#include "trade_cancel_other_event.hpp"
#include "trade_finished_event.hpp"
#include "cards_response_event.hpp"
#include "trade.hpp"

class TradeStatusEvent : public LobbyPacketEvent {
public:
	TradeStatusEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t targetPlayerId = pack.ReadInt();
		uint8_t state = pack.ReadByte(); // 50 = cancel, 51 = confirm (lock trade), 52 = yes (finish trade)
		if (state == 50)
		{
			// Remove them from the trades
			trades.erase(session->Info()->Id());
			trades.erase(targetPlayerId);

			session->Send(TradeCancelSelfEvent{ targetPlayerId, state }.Compose(session));

			auto target = session->GetLobby()->FindSession(targetPlayerId);
			if (target != nullptr)
				target->Send(TradeCancelOtherEvent{ session->Info()->Id(), state }.Compose(target.get()));
		}
		else if (state == 51)
		{
			// Client pressed confirm, notify other client
			session->Send(TradeCancelSelfEvent{ targetPlayerId, state }.Compose(session));

			auto target = session->GetLobby()->FindSession(targetPlayerId);
			if (target != nullptr)
				target->Send(TradeCancelOtherEvent{ session->Info()->Id(), state }.Compose(target.get()));
		}
		else if (state == 52)
		{
			// Neither of the two players added any items, this shouldn't happen, but a check is always good incase they're messing with packets
			if (!trades.count(session->Info()->Id()) && !trades.count(targetPlayerId))
				return;

			if (!trades.count(targetPlayerId) || !trades[targetPlayerId].didFinish)
			{
				// Other player didn't press yes yet, so store this player, and then wait for the other player to also press yes
				if (!trades.count(session->Info()->Id()))
				{
					TradeInfo info{};
					info.didFinish = true;

					trades.emplace(session->Info()->Id(), info);
				}
				else
					trades[session->Info()->Id()].didFinish = true;
			}
			else
			{
				// Other player has also pressed yes to finish the trade, meaning we should end the trade
				std::vector<uint64_t> myProposedItems = trades[session->Info()->Id()].proposedItems;
				std::vector<uint64_t> targetProposedItems = trades[targetPlayerId].proposedItems;

				// Remove both trades from the map, they're not needed anymore.
				// They might not both be stored, if one player didn't add any items, and also was the last to accept the trade, this however is no problem, erase will simply return 0
				trades.erase(session->Info()->Id());
				trades.erase(targetPlayerId);

				auto target = session->GetLobby()->FindSession(targetPlayerId);
				if (target != nullptr)
				{
					// Actually trade the items
					for (uint64_t proposedItemId : myProposedItems)
					{
						InventoryCard card = session->Inventory()->GetItemByCardId(proposedItemId);
						card.ownerId = targetPlayerId;

						target->Inventory()->AddItem(card);
						session->Inventory()->RemoveItem(proposedItemId);
					}

					for (uint64_t proposedItemId : targetProposedItems)
					{
						InventoryCard card = target->Inventory()->GetItemByCardId(proposedItemId);
						card.ownerId = session->Info()->Id();

						session->Inventory()->AddItem(card);
						target->Inventory()->RemoveItem(proposedItemId);
					}

					// Update both players their inventories
					std::vector<InventoryCard> cards = session->Inventory()->List();
					session->Send(CardsResponseEvent{ cards }.Compose(session));

					cards = target->Inventory()->List();
					target->Send(CardsResponseEvent{ cards }.Compose(target.get()));

					// Notify both players that the trade has succesfully ended
					session->Send(TradeFinishedEvent{ targetPlayerId }.Compose(session));
					target->Send(TradeFinishedEvent{ session->Info()->Id() }.Compose(target.get()));
				}
			}
		}
	}
};

#endif