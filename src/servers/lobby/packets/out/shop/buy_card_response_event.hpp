#ifndef BUY_CARD_RESPONSE_EVENT_HPP
#define BUY_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "inventory_card.hpp"

class BuyCardResponseEvent : public LobbyPacketEvent {

public:
	BuyCardResponseEvent(InventoryCard card, bool isCash, uint32_t newCurrencyAmount) { m_card = card; m_isCash = isCash; m_balance = newCurrencyAmount; };

	ServerPacket Compose(LobbySession* session) override {
		Packets::Lobby::BuyItemRsp rsp{};


		auto packet = ServerPacket::Create<Opcode::LOBBY_BUY_ITEM_RSP>();

		packet.WriteByte(m_isCash);
		packet.WriteInt(m_balance);
		packet.WriteInt(0); // unknown;
		packet.WriteByte(1); // card count

		// card
		packet.WriteLong(m_card.id);
		packet.WriteInt(m_card.itemId);
		packet.WriteByte(0); // unknown
		packet.WriteByte(m_card.itemType);
		packet.WriteByte(0); // unknown
		packet.WriteFlag(true); // giftable
		packet.WriteEmpty(6);
		packet.WriteInt(m_card.timeCreated);
		packet.WriteFlag(true); // opened
		packet.WriteShort(0); // unknown
		packet.WriteFlag(false); // hidden
		packet.WriteByte(2); // unknown
		packet.WriteShort(m_card.period);
		packet.WriteByte(m_card.periodType);
		packet.WriteFlag(true); // unknown
		packet.WriteShort(m_card.boostLevel);
		packet.WriteFlag(m_card.boostLevel > 0); // is boosted
		packet.WriteFlag(false); // unknown
		packet.WriteInt(0); // unknown
		
		return packet;
	};
private:
	InventoryCard m_card;
	bool m_isCash;
	uint32_t m_balance;
};

#endif