#ifndef SET_OFFLINE_EVENT_HPP
#define SET_OFFLINE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class SetOfflineEvent : public LobbyPacketEvent {

public:
	SetOfflineEvent(uint32_t targetId) { _targetId = targetId; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_BUDDY_SET_OFFLINE>();

		packet.WriteInt(_targetId);

		return packet;
	};
private:
	uint32_t _targetId;
};

#endif