#ifndef OPEN_CARD_EVENT_HPP
#define OPEN_CARD_EVENT_HPP

#include <cstdint>
#include <memory>
#include <string>
#include "lobby_packet_event.hpp"
#include "inventory_manager.hpp"
#include "lobby_session.hpp"
#include "inventory_card.hpp"
#include "open_card_response_event.hpp"
#include <vector>
#include "cards_response_event.hpp"

class OpenCardEvent : public LobbyPacketEvent {

public:
	OpenCardEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t cardId = pack.ReadInt();
		uint32_t unk01 = pack.ReadInt();
		pack.Skip(8);

		InventoryCard inventoryCard = session->Inventory()->GetItemByCardId(cardId);

		if (session->Inventory()->OpenGift(inventoryCard.id))
			session->Send(OpenCardResponseEvent{ inventoryCard, session->Info()->Don() }.Compose(session));

		std::vector<InventoryCard> cards = session->Inventory()->List();
		session->Send(CardsResponseEvent{cards}.Compose(session));
	}
};

#endif