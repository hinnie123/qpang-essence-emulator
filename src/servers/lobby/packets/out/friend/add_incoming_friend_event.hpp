#ifndef ADD_INCOMING_FRIEND_EVENT_HPP
#define ADD_INCOMING_FRIEND_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"

class AddIncomingFriendEvent : public LobbyPacketEvent {

public:
	AddIncomingFriendEvent(Friend theFriend) { _friend = theFriend; };

	ServerPacket Compose(LobbySession* session) override {


		auto packet = ServerPacket::Create<Opcode::LOBBY_FRIEND_INVITE_RSP>();

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