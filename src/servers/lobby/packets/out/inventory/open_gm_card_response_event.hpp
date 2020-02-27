#ifndef OPEN_GM_CARD_RESPONSE_EVENT_HPP
#define OPEN_GM_CARD_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>
#include "inventory_card.hpp"
#include <string>
#include <time.h>
#include "string_converter.hpp"

class OpenGMCardResponseEvent : public LobbyPacketEvent {

public:
	OpenGMCardResponseEvent(InventoryCard card) { _card = card; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_OPEN_GM_CARD_RSP>();

		packet.WriteLong(_card.id);
		packet.WriteInt(_card.itemId);
		packet.WriteByte(0); // unknown;
		packet.WriteByte(_card.itemType);
		packet.WriteByte(0); // unknown
		packet.WriteFlag(_card.giftable);
		packet.WriteEmpty(6);
		packet.WriteInt(_card.timeCreated);
		packet.WriteFlag(true); // opened
		packet.WriteShort(0); // unknown
		packet.WriteFlag(false); // hidden
		packet.WriteByte(2); // unknown
		packet.WriteShort(_card.period);
		packet.WriteByte(_card.periodType);
		packet.WriteFlag(true); // unknown
		packet.WriteShort(_card.boostLevel);
		packet.WriteFlag(_card.boosted);
		packet.WriteFlag(false); // unknown
		packet.WriteInt(0); // unknown

		return packet;
	};
private:
	InventoryCard _card;
};

#endif