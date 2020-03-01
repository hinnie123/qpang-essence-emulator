#ifndef DROP_CARD_EVENT_HPP
#define DROP_CARD_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "drop_card_response_event.hpp"
#include "inventory_manager.hpp"
#include "lobby_session.hpp"

class DropCardEvent : public LobbyPacketEvent {

public:
	DropCardEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint64_t cardId = pack.ReadLong();
		uint32_t unk01 = pack.ReadInt();

		if (session->Inventory()->RemoveItem(cardId))
			session->Send(DropCardResponseEvent{ static_cast<uint32_t>(cardId) }.Compose(session));

	}
};

#endif