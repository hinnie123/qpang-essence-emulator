#ifndef RECEIVE_GIFT_EVENT_HPP
#define RECEIVE_GIFT_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>
#include "inventory_card.hpp"
#include <string>
#include <time.h>
#include "string_converter.hpp"

class ReceiveGiftEvent : public LobbyPacketEvent {

public:
	ReceiveGiftEvent(InventoryCard card, std::string senderName) { _card = card; _senderName = senderName; };
	
	ServerPacket Compose(LobbySession* session) override {
		
		auto packet = ServerPacket::Create<Opcode::LOBBY_RECEIVE_GIFT>();

		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_senderName), 16);
		packet.WriteInt(_card.id);
		packet.WriteInt(0); // unknown
		packet.WriteFlag(true); // unknown
		packet.WriteLong(_card.timeCreated);

		return packet;
	};
private:
	InventoryCard _card;
	std::string _senderName;
};

#endif