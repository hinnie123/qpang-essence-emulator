#ifndef UPDATE_PLAYER_EVENT_HPP
#define UPDATE_PLAYER_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"
#include <array>
#include <cstdint>
#include "update_player_response_event.hpp"

class UpdatePlayerEvent : public SquarePacketEvent
{
public:
	UpdatePlayerEvent() : SquarePacketEvent(sizeof(Packets::Square::ParkPlayerUpdate)) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		pack.Skip(4);
		uint16_t character = pack.ReadShort();
		std::array<uint32_t, 9> equipment = pack.ReadArray<uint32_t, 9>();
		uint32_t unknown1 = pack.ReadInt();
		uint32_t unknown2 = pack.ReadInt();

		auto square = session->GetSquare();
		if (square == nullptr) return;

	
		// TODO: Move this & validate equipment
		std::array<uint32_t, 9> currEquipment = session->Info()->Equipment();
		for (size_t i = 0; i < equipment.size(); i++)
		{
			currEquipment[i] = equipment[i];
		}

		session->Info()->SetEquipment(equipment);
		session->Info()->SetCharacter(character);

		square->SendPacket(UpdatePlayerResponseEvent{ session->Info()->Id(), character, session->Info()->Equipment() }.Compose(session));

	};
};


#endif // !UPDATE_PLAYER_EVENT_HPP
