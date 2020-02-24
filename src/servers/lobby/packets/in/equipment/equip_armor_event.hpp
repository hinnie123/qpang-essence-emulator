#ifndef EQUIP_ARMOR_EVENT_HPP
#define EQUIP_ARMOR_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "equipment_manager.hpp"
#include "equip_armor_response_event.hpp"
#include "info_manager.hpp"
#include <cstdint>
#include <array>

class EquipArmorEvent : public LobbyPacketEvent {

public:
	EquipArmorEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::EquipArmour)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint16_t characterOffset = session->Equipment()->GetCharacterIndex(session->Info()->Character());

		uint64_t head = pack.ReadLong();
		uint64_t face = pack.ReadLong();
		uint64_t body = pack.ReadLong();
		uint64_t hands = pack.ReadLong();
		uint64_t pants = pack.ReadLong();
		uint64_t shoes = pack.ReadLong();
		uint64_t back = pack.ReadLong();
		uint64_t side = pack.ReadLong();

		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::HEAD, head);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::FACE, face);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::BODY, body);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::HAND, hands);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::BOTTOM, pants);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::FOOT, shoes);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::BACK, back);
		session->Equipment()->SetEquipmentPart((EquipmentManager::Character)characterOffset, EquipmentManager::EquipmentSlot::SIDE, side);

		std::array<uint64_t, 9> equipment = session->Equipment()->GetArmor((EquipmentManager::Character)characterOffset);

		session->Send(EquipArmorResponseEvent{ equipment, characterOffset }.Compose(session));
	}
};

#endif