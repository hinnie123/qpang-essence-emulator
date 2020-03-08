#ifndef REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP
#define REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP

#include "packet_data.hpp"
#include <cstdint>
#include <vector>
#include <memory>
#include "square.hpp"
#include "square_packet_event.hpp"
#include "square_manager.hpp"
#include "login_response_event.hpp"
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class RequestEquipmentResponseEvent : public SquarePacketEvent {

public:
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		uint8_t rank = pack.ReadByte();
		uint16_t level = pack.ReadShort();
		uint16_t character = pack.ReadShort();
		uint32_t prestige = pack.ReadInt();
		uint8_t success = pack.ReadFlag();
		std::u16string nickname = pack.ReadUtf16String(16);
		std::array<uint32_t, 9> equipment = pack.ReadArray<uint32_t, 9>();

		if (success)
		{
			auto targetSession = session->GetSquareManager()->FindSession(playerId);
			std::vector<Square::Ptr> squares = session->GetSquareManager()->List();

			if (targetSession != nullptr)
			{
				targetSession->Info()->SetState(0);
				targetSession->Info()->SetId(playerId);
				targetSession->Info()->SetCharacter(character);
				targetSession->Info()->SetEquipment(equipment);
				targetSession->Info()->SetRank(rank);
				targetSession->Info()->SetLevel(level);
				targetSession->Info()->SetPrestige(prestige);
				targetSession->Info()->SetNickname(nickname);

				targetSession->Send(LoginResponseEvent{ squares }.Compose(targetSession.get()));
			}
		}
	}
};

#endif