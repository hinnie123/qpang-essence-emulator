#ifndef CARDS_RESPONSE_EVENT_HPP
#define CARDS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "inventory_card.hpp"

class CardsResponseEvent : public LobbyPacketEvent {

public:
	CardsResponseEvent(std::vector<InventoryCard> cards) { _cards = cards; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::InventoryCardsRsp rsp{};
		
		auto packet = ServerPacket::Create<Opcode::LOBBY_INVENTORY_CARDS_RSP>();
		
		uint32_t size = _cards.size();

		packet.WriteShort(size);
		packet.WriteShort(size);
		packet.WriteShort(size);

		for (size_t i = 0; i < size; i++)
		{
			InventoryCard card = _cards.at(i);
			
			packet.WriteLong(card.id);
			packet.WriteInt(card.itemId);
			packet.WriteByte(10);
			packet.WriteByte(card.itemType);
			packet.WriteByte(10);
			packet.WriteFlag(card.giftable);
			packet.WriteEmpty(6);
			packet.WriteInt(card.timeCreated);
			packet.WriteFlag(card.opened);
			packet.WriteShort(10);
			packet.WriteFlag(false); // hidden
			packet.WriteByte(1);
			packet.WriteShort(card.period);
			packet.WriteByte(card.periodType);
			packet.WriteFlag(true);
			packet.WriteShort(card.boostLevel);
			packet.WriteFlag(card.boosted);
			packet.WriteFlag(true);
			packet.WriteEmpty(4);
		}

		return packet;
	};
private:
	std::vector<InventoryCard> _cards;
};

#endif