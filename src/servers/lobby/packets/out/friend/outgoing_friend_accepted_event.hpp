#ifndef OUTGOING_FRIEND_ACCEPTED_EVENT_HPP
#define OUTGOING_FRIEND_ACCEPTED_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"
#include "friend_manager.hpp"

class OutgoingFriendAcceptedEvent : public LobbyPacketEvent {

public:
	OutgoingFriendAcceptedEvent(Friend theFriend) { _friend = theFriend; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_OUTGOING_FRIEND_ACCEPTED>();

		packet.WriteInt(_friend.toPlayerId);
		packet.WriteShort(0); // unknown
		packet.WriteShort(0); // unknown
		packet.WriteByte(_friend.state);
		packet.WriteFlag(true);
		packet.WriteShort(_friend.level);
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_friend.nickname), 16);

		return packet;
	};
private:
	Friend _friend;
};

#endif