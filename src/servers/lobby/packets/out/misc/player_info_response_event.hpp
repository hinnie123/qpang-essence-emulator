#ifndef PLAYER_INFO_RESPONSE_EVENT_HPP
#define PLAYER_INFO_RESPONSE_EVENT_HPP

#include <memory>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include <cstdint>
#include <string>
#include "string_converter.hpp"
#include "equipment_manager.hpp"

class PlayerInfoResponseEvent : public LobbyPacketEvent {

public:
	PlayerInfoResponseEvent(uint32_t playerId, std::u16string nickname ,uint32_t level, uint32_t rank, uint32_t character, uint32_t experience, std::array<uint32_t, 13> equipment)
	{ 
		_playerId = playerId;
		_nickname = nickname;
		_level = level;
		_rank = rank;
		_character = character;
		_experience = experience;
		_equipment = equipment;
	};

	ServerPacket Compose(LobbySession* session) override 
	{
		auto packet = ServerPacket::Create<Opcode::LOBBY_PLAYERINFO_RSP>();

		packet.WriteInt(_playerId);
		packet.WriteEmpty(42);
		packet.WriteUtf16String(_nickname, 16); // TODO: Change this
		packet.WriteInt(0); // playtime
		packet.WriteEmpty(4); // unknown
		packet.WriteByte(_level);
		packet.WriteByte(_rank);
		
		// Character information
		packet.WriteShort(_character);
		
		for (size_t i = 0; i < 9; i++)
		{
			packet.WriteInt(_equipment[i]);
		}

		for (size_t i = 9; i < _equipment.size(); i++)
		{
			packet.WriteInt(_equipment[i]);
			packet.WriteInt(0); // unknown
		}

		packet.WriteEmpty(40);
		packet.WriteInt(_experience);

		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown
		packet.WriteInt(0); // unknown

		packet.WriteShort(1000); // slacker points

		packet.WriteInt(1); // unknown

		packet.WriteInt(2); // leaderboard rank
		packet.WriteInt(4); // leaderboard gained

		for (size_t i = 0; i < 40; i++)
		{
			packet.WriteInt(0); // title id
			packet.WriteInt(0); // unknown
		}

		return packet;
	};

private:
	uint32_t _playerId;
	std::u16string _nickname;
	uint32_t _level;
	uint32_t _rank;
	uint32_t _character;
	uint32_t _experience;
	std::array<uint32_t, 13> _equipment;
	
};

#endif