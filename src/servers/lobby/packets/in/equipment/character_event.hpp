#ifndef CHARACTER_EVENT_HPP
#define CHARACTER_EVENT_HPP

#include "lobby_packet_event.hpp"
#include <cstdint>

#include "character_response_event.hpp"
#include "info_manager.hpp"
#include "lobby_session.hpp"

class CharacterEvent : public LobbyPacketEvent {

public:
	CharacterEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::CharacterChange)) {};

	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint16_t characterId = pack.ReadShort();
		uint32_t unknown = pack.ReadInt();

		if (session->Info()->Character() == characterId)
			return; // not supposed to happen.

		session->Info()->Character(characterId);
		session->Send(CharacterResponseEvent{ characterId }.Compose(session));
	}
};

#endif