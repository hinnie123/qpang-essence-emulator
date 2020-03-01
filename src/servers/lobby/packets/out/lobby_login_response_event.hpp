#ifndef LOBBY_LOGIN_RESPONSE_EVENT_HPP
#define LOBBY_LOGIN_RESPONSE_EVENT_HPP

#include <cstdint>
#include <memory>

#include "equipment_manager.hpp"
#include "inventory_manager.hpp"
#include "lobby_packet_event.hpp"
#include "friend_manager.hpp"
#include "string_converter.hpp"


class LoginResponseEvent : public LobbyPacketEvent {

public:
	LoginResponseEvent(uint32_t userId) { _userId = userId; };

	ServerPacket Compose(LobbySession* session) override
	{
		auto player = session->GetLobby()->FindSessionByUid(_userId);

		//Already logged in, let's disconnect the currenty logged in user.
		if (player != nullptr)
		{
			sLogger->Get()->debug("LoginResponse Already Logged In");

			player->HandleClose();
			player->Disconnect();
		}

		auto packet = ServerPacket::Create<Opcode::LOBBY_LOGIN_RSP>();

		session->userId = _userId;
		session->Info()->Load(_userId);
		session->Equipment()->Load(session->Info()->Id());
		session->Inventory()->Load(session->Info()->Id());
		session->Messenger()->Load(session->Info()->Id());
		session->Friends()->Load(session->Info()->Id());

		/* Player info */
		packet.WriteInt(_userId);
		packet.WriteEmpty(42);
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(session->Info()->Nickname()), 16);
		packet.WriteInt(100); // playtime
		packet.WriteInt(session->Info()->Cash());
		packet.WriteInt(session->Info()->Rank());
		packet.WriteShort(299); // unknown
		packet.WriteShort(session->Info()->Character());
		packet.WriteInt(session->Info()->Level());
		packet.WriteEmpty(8);

		/* Player settings */
		packet.WriteFlag(true); // accept PM
		packet.WriteFlag(true); // accept game invites
		packet.WriteFlag(true); // accept friend invites
		packet.WriteFlag(false); // unknown
		packet.WriteFlag(true); // accept trade requests
		packet.WriteEmpty(20);
		packet.WriteByte(4); // current tutorial stage (unlock everything)
		packet.WriteEmpty(12);

		/* Player storage */
		packet.WriteShort(200); // max inventory size
		packet.WriteShort(50); // max friendlist size
		packet.WriteShort(10); // max outgoing/(incoming?) friendlist size
		packet.WriteShort(50); // daily max memo send count
		packet.WriteShort(50); // daily memo send count
		
		/* Player stats */
		packet.WriteInt(1); // unknown
		packet.WriteInt(session->Info()->Experience());
		packet.WriteInt(session->Info()->Don());
		packet.WriteInt(1); // unknown
		packet.WriteInt(0); // kill amount
		packet.WriteInt(0); // death amount

		/* Player match stats */
		packet.WriteInt(0); // team games won
		packet.WriteInt(0); // team games lost
		packet.WriteInt(0); // team games drew
		packet.WriteInt(1); // unknown
		packet.WriteInt(0); // mission games won
		packet.WriteInt(0); // mission games lost
		packet.WriteInt(0); // mission games drew

		packet.WriteEmpty(72);
		packet.WriteInt(1); // slacker points
		packet.WriteInt(session->Info()->Coins());
		packet.WriteEmpty(44);

		/* Player character equipment */
		std::array<std::array<uint64_t, 13>, 6> allEquipment = session->Equipment()->GetAll();
		for (size_t i = 0; i < 6; i++)
		{
			std::array<uint64_t, 13> characterEquipment = allEquipment[i];

			packet.WriteShort(session->Equipment()->GetCharacterCode(i));

			for (size_t y = 0; y < 9; y++)
			{
				packet.WriteLong(characterEquipment[y]);
			}

			for (size_t y = 9; y < 13; y++)
			{
				packet.WriteLong(characterEquipment[y]);
				packet.WriteLong(0); // unknown
			}
		}

		/* TODO: Player title information */
		packet.WriteEmpty(1500);


		return packet;
	};
private:
	uint32_t _userId;
};

#endif