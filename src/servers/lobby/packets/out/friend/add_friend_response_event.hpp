#ifndef ADD_FRIEND_RESPONSE_EVENT_HPP
#define ADD_FRIEND_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "friend.hpp"
#include "friend_manager.hpp"
#include "string_converter.hpp"

class AddFriendResponseEvent : public LobbyPacketEvent {

public:
	AddFriendResponseEvent(Friend theFriend, bool isOnline, wchar_t nickname[17]) { _friend = theFriend; _isOnline = isOnline; wcscpy(_nickname, nickname); };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_FRIEND_INVITE_RSP>();

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
	wchar_t _nickname[17];
};

#endif