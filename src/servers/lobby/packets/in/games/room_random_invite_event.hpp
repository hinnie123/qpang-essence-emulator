#ifndef ROOM_RANDOM_INVITE_EVENT_HPP
#define ROOM_RANDOM_INVITE_EVENT_HPP

#include "lobby_packet_event.hpp"

class RoomRandomInviteEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t roomId = pack.ReadInt();
		uint32_t unk01 = pack.ReadInt();
	}
};

#endif