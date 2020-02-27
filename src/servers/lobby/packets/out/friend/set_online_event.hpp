#ifndef SET_ONLINE_EVENT_HPP
#define SET_ONLINE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <cstdint>

class SetOnlineEvent : public LobbyPacketEvent {

public:
	SetOnlineEvent(uint32_t targetId) { _targetId = targetId; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_BUDDY_SET_ONLINE>();

		packet.WriteInt(_targetId);

		return packet;
	};
private:
	uint32_t _targetId;
};

#endif