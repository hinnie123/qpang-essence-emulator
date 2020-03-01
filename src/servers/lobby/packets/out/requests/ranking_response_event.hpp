#ifndef RANKING_RESPONSE_EVENT_HPP
#define RANKING_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "opcodes.hpp"
#include "leaderboard.hpp"

class RankingResponseEvent : public LobbyPacketEvent {

public:
	RankingResponseEvent(Leaderboard::Position rank) { _rank = rank; };

	ServerPacket Compose(LobbySession* session) override 
	{
		auto packet = ServerPacket::Create < Opcode::LOBBY_PLAYER_RANKING_RSP>();

		packet.WriteInt(0); // unk
		packet.WriteInt(_rank.rank);
		packet.WriteInt(_rank.difference);

		return packet;
	};
private:
	Leaderboard::Position _rank;
};

#endif