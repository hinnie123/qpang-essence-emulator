#ifndef FRIEND_REMOVED_FRIEND_EVENT_HPP
#define FRIEND_REMOVED_FRIEND_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class FriendRemovedFriendEvent : public LobbyPacketEvent {

public:
	FriendRemovedFriendEvent(uint32_t targetId, std::u16string nickname) { _targetId = targetId; _nickname = nickname; };

	ServerPacket Compose(LobbySession* session) override 
	{
		auto packet = ServerPacket::Create<Opcode::LOBBY_FRIEND_REMOVE_FRIEND>();

		packet.WriteInt(_targetId);
		packet.WriteLong(0); // unknown
		packet.WriteUtf16String(_nickname, 16);

		return packet;
	};
private:
	uint32_t _targetId;
	std::u16string _nickname;
};

#endif