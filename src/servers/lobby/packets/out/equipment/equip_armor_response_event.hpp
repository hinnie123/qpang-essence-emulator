#ifndef EQUIP_ARMOR_RESPONSE_EVENT_HPP
#define EQUIP_ARMOR_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>
#include "equipment_manager.hpp"


class EquipArmorResponseEvent : public LobbyPacketEvent {

public:
	EquipArmorResponseEvent(std::array<uint64_t, 9> equipment, uint16_t characterOffset) { _equipment = equipment; _characterOffset = characterOffset; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_EQUIP_ARMOUR_RSP>();

		packet.WriteShort(_characterOffset);

		for (size_t i = 0; i < 8; i++)
		{
			packet.WriteLong(_equipment[i]);
		}

		return packet;
	};
private:
	std::array<uint64_t, 9> _equipment;
	uint16_t _characterOffset;
};

#endif