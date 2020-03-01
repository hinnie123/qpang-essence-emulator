#ifndef NEW_GAMEROOM_EVENT_HPP
#define NEW_GAMEROOM_EVENT_HPP

#include <memory>
#include "game_room.hpp"
#include "packet_event.hpp"
#include "connection.hpp"
#include "opcodes.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"

class UpdateGameRoomEvent : public PacketEvent
{
public:
	UpdateGameRoomEvent(GameRoom::Ptr room) { 
		m_identifier = room->GetIdentifier();
		m_map = room->GetMap();
		m_melee = false;
		m_currentPlayers = room->GetPlayerCount();
		m_maxPlayers = room->GetMaxPlayerCount();
		m_modeIdentifier = room->GetMode()->GetModeIdentifier();
		m_state = room->GetState();
		m_name = room->GetName();
	};

	ServerPacket Compose(Connection::Ptr conn)
	{
		auto packet = ServerPacket::Create<Opcode::UPDATE_GAMEROOM>();

		packet.WriteInt(m_identifier);
		packet.WriteByte(m_map);
		packet.WriteByte(m_modeIdentifier);
		packet.WriteByte(m_currentPlayers);
		packet.WriteByte(m_maxPlayers);
		packet.WriteByte(m_melee);
		packet.WriteByte(m_state);
		packet.WriteUtf16String(m_name, 30);
	
		return packet;
	}
private:
	uint32_t m_identifier;
	uint8_t m_map;
	uint8_t m_melee;
	uint8_t m_currentPlayers;
	uint8_t m_maxPlayers;
	uint8_t m_modeIdentifier;
	uint8_t m_state;
	std::u16string m_name;
};

#endif // !NEW_GAMEROOM_EVENT_HPP
