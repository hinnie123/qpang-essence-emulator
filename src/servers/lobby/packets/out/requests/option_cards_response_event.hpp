#ifndef OPTION_CARDS_RESPONSE_EVENT_HPP
#define OPTION_CARDS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "inventory_card.hpp"
#include "string_converter.hpp"

class GiftsResponseEvent : public LobbyPacketEvent {

public:
	GiftsResponseEvent(std::vector<InventoryCard> cards) { _cards = cards; };


	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_GIFTS_RSP>();

		packet.WriteShort(_cards.size());
		packet.WriteShort(_cards.size());
		packet.WriteShort(_cards.size());

		for (size_t i = 0; i < _cards.size(); i++)
		{
			InventoryCard card = _cards.at(i);

			packet.WriteUtf16String(u"Admin", 16);
			packet.WriteInt(card.id);
			packet.WriteInt(0);
			packet.WriteFlag(false);
			packet.WriteLong(card.timeCreated);
		}

		return packet;
	};
private:
	std::vector<InventoryCard> _cards;
};

#endif