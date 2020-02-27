#ifndef ACCEPT_INCOMING_FRIEND_RESPONSE_EVENT_HPP
#define ACCEPT_INCOMING_FRIEND_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"

class AcceptIncomingFriendResponseEvent : public LobbyPacketEvent {

public:
	AcceptIncomingFriendResponseEvent(Friend theFriend, bool isOnline) { _friend = theFriend; _isOnline = isOnline; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_ACCEPT_INCOMING_FRIEND_RSP>();

		packet.WriteInt(_friend.toPlayerId);
		packet.WriteShort(0); // unknown
		packet.WriteShort(0); // unknown
		packet.WriteByte(_friend.state);
		packet.WriteFlag(_isOnline);
		packet.WriteShort(_friend.level);
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_friend.nickname), 16);

		return packet;
	};
private:
	Friend _friend;
	bool _isOnline;
};

#endif