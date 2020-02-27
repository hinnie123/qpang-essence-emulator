#ifndef GOODS_RESPONSE_EVENT_HPP
#define GOODS_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "shop_item.hpp"

class GoodsResponseEvent : public LobbyPacketEvent {

public:
	GoodsResponseEvent(std::vector<ShopItem> items) { _items = items; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_NORMAL_GOODS>();

		packet.WriteShort(_items.size());
		packet.WriteShort(_items.size());
		packet.WriteShort(_items.size());;

		for (size_t i = 0; i < _items.size(); i++)
		{
			ShopItem item = _items.at(i); 
			
			packet.WriteInt(item.sequenceId);
			packet.WriteInt(item.itemId);
			packet.WriteFlag(item.payType); // is cash
			packet.WriteInt(item.price);
			packet.WriteInt(item.stock);
			packet.WriteByte(item.state);
		}

		return packet;
	};
private:
	std::vector<ShopItem> _items;
};

#endif