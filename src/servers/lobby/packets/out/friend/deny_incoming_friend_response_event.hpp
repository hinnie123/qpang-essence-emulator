#ifndef DENY_INCOMING_FRIEND_RESPONSE_EVENT_HPP
#define DENY_INCOMING_FRIEND_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"

class DenyIncomingFriendResponseEvent : public LobbyPacketEvent {

public:
	DenyIncomingFriendResponseEvent(uint32_t playerId) { _playerId = playerId; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_DENY_INCOMING_FRIEND_RSP>();

		packet.WriteInt(_playerId);
		packet.WriteLong(0); // unknown
		packet.WriteUtf16String(u"Test", 16);
		
		return packet;
	};
private:
	uint32_t _playerId;
};

#endif