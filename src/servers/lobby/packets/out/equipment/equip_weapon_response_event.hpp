#ifndef EQUIP_WEAPON_RESPONSE_EVENT_HPP
#define EQUIP_WEAPON_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>


class EquipWeaponResponseEvent : public LobbyPacketEvent {

public:
	EquipWeaponResponseEvent(std::array<uint64_t, 4> equipment, uint16_t characterOffset) { _equipment = equipment; _characterOffset = characterOffset; };

	ServerPacket Compose(LobbySession* session) override {
		
		auto packet = ServerPacket::Create<Opcode::LOBBY_EQUIP_WEAPON_RSP>();

		packet.WriteShort(_characterOffset);

		for (size_t i = 0; i < 4; i++)
		{
			packet.WriteLong(_equipment[i]);
			packet.WriteLong(0);
		}

		return packet;
	};
private:
	std::array<uint64_t, 4> _equipment;
	uint16_t _characterOffset;
};

#endif