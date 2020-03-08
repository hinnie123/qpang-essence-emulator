#ifndef FRIEND_RESPONSE_EVENT_HPP
#define FRIEND_RESPONSE_EVENT_HPP

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "friend.hpp"
#include "string_converter.hpp"
#include "lobby.hpp"
#include "lobby_session.hpp"

class FriendsResponseEvent : public LobbyPacketEvent {

public:
	FriendsResponseEvent(uint32_t totalSent, uint32_t totalCount, std::vector<Friend> friends) { _totalSent = totalSent, _totalCount = totalCount, _friends = friends; };

	ServerPacket Compose(LobbySession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::LOBBY_BUDDIES_RSP>();

		packet.WriteShort(_totalSent);
		packet.WriteShort(_totalCount);
		packet.WriteShort(_friends.size());

		for (size_t i = 0; i < _friends.size(); i++)
		{
			Friend f = _friends.at(i);

			packet.WriteInt(f.id);
			packet.WriteEmpty(4);
			packet.WriteByte(f.state);
			packet.WriteFlag(false); // is online
			packet.WriteShort(f.level);
			packet.WriteUtf16String(f.nickname, 16);
		}

		return packet;
	}

private:
	uint32_t _totalSent;
	uint32_t _totalCount;
	std::vector<Friend> _friends;
};

#endif