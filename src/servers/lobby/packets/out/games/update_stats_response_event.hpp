#ifndef UPDATE_STATS_RESPONSE_EVENT_HPP
#define UPDATE_STATS_RESPONSE_EVENT_HPP

#include <memory>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"

class UpdateStatsResponseEvent : public LobbyPacketEvent {

public:
	UpdateStatsResponseEvent()
	{	
	}

	ServerPacket Compose(LobbySession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::LOBBY_ROOM_REQUEST_STATS_RSP>();

		packet.WriteInt(session->Info()->Id());
		packet.WriteInt(session->Info()->Experience());
		packet.WriteInt(session->Info()->Don());
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // kills
		packet.WriteInt(0); // deaths
		packet.WriteInt(0); // team game win
		packet.WriteInt(0); // team game lose
		packet.WriteInt(0); // team game draw
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // mission game win
		packet.WriteInt(0); // mission game lose
		packet.WriteInt(0); // mission game draw
		packet.WriteEmpty(72);
		packet.WriteInt(0); // slacker points
		packet.WriteInt(session->Info()->Coins());

		return packet;
	}
private:
};

#endif