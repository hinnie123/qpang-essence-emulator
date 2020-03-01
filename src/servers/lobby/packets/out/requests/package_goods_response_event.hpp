#ifndef PACKAGE_GOODS_RESPONSE_EVENT_HPP
#define PACKAGE_GOODS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>

class PackageGoodsResponseEvent : public LobbyPacketEvent {

public:
	PackageGoodsResponseEvent() {  };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_REQUEST_PACKAGE_GOODS_RSP>();

		packet.WriteShort(0);
		packet.WriteShort(0);
		packet.WriteShort(0);

		return packet;
	};
private:
};

#endif