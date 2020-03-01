#ifndef REGISTER_CHARACTERS_EVENT_HPP
#define REGISTER_CHARACTERS_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"
#include "database.hpp"
#include <boost/format.hpp>
#include <string>
#include "equipment_manager.hpp"
#include "register_characters_response_event.hpp"

class RegisterCharactersEvent : public LobbyPacketEvent {

public:
	RegisterCharactersEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::u16string nickname = pack.ReadUtf16String(16);
		std::u16string referrerNickname = pack.ReadUtf16String(16);
		uint16_t firstCharacter = pack.ReadShort();
		uint16_t secondCharacter = pack.ReadShort();

		if (!session->Equipment()->ValidateCharacter(firstCharacter) || !session->Equipment()->ValidateCharacter(secondCharacter))
			return;

		if (session->GetLobby()->ValidateNickname(StringConverter::Utf16ToUtf8(nickname)))
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(820);

		Database database{};
		std::string query = str(boost::format("INSERT INTO players (user_id, name) VALUES (%1%, %2%)") % std::to_string(session->userId) % database.escapeString(StringConverter::Utf16ToUtf8(nickname)));
		database.executeQuery(query);

		uint32_t playerId = database.getLastInsertId();
		if (playerId == NULL)
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(836);

		query = "INSERT INTO player_equipment (player_id, character_id) VALUES ";
		for (size_t i = 0; i < EquipmentManager::Character::CHARACTER_COUNT; i++)
		{
			query += str(boost::format("(%1%, %2%),")
				% playerId % session->Equipment()->GetCharacterCode(i));
		}
		database.executeQuery(query.substr(0, query.size() - 1)); // getting rid of ','
		database.Close();

		session->Info()->Nickname(StringConverter::Utf16ToUtf8(nickname));
		session->Send(RegisterCharactersResponseEvent{ StringConverter::Utf16ToUtf8(nickname), firstCharacter, secondCharacter }.Compose(session));
	};
};

#endif