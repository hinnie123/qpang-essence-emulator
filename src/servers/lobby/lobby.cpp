#include "lobby.hpp"
#include "lobby_session.hpp"

#include "packet_data.hpp"
#include "handshake_event.hpp"
#include "gamerooms_event.hpp"
#include "job_scheduler.hpp"


Lobby::Lobby()
{
}

Lobby::~Lobby()
{
	//
}

void Lobby::RemoveSession(uint32_t userId)
{
	for (auto it = _sessions.begin(); it != _sessions.end(); it++)
	{
		if ((*it)->userId == userId)
		{
			(*it)->Save();
			Channels()->RemovePopulation((*it)->Info()->Channel());
			_sessions.erase(it);
			return;
		}
	}
}

OfflinePlayer Lobby::GetOfflinePlayer(uint32_t playerId, OfflinePlayer::Type type)
{
	std::string query = "SELECT * FROM players WHERE players.id = %1%";
	return ConstructOfflinePlayer(str(boost::format(query) % playerId), type);
}

OfflinePlayer Lobby::GetOfflinePlayer(std::u16string nickname, OfflinePlayer::Type type)
{
	std::string escNickname = sDatabase->escapeString(StringConverter::Utf16ToUtf8(nickname));
	std::string query = "SELECT * FROM players WHERE players.name = %1%";
	return ConstructOfflinePlayer(str(boost::format(query) % escNickname), type);
}

void Lobby::RefreshGamerooms()
{

}

LobbySession::Ptr Lobby::FindSession(std::array<uint8_t, 16> uuid)
{
	for (auto session : _sessions)
		if (session->Info()->Uuid() == uuid)
			return session;

	return nullptr;
}

void Lobby::AddSession(std::shared_ptr<LobbySession> session)
{
	session->StartNetworking();
	_sessions.push_back(session);
}

std::shared_ptr<LobbySession> Lobby::FindSessionByUid(uint32_t userId)
{
	if (userId == NULL)
		return nullptr;

	for (auto session : _sessions)
		if (session->userId == userId)
			return session;

	return nullptr;
}

LobbySession::Ptr Lobby::FindSession(uint32_t playerId)
{
	if (playerId == NULL)
		return nullptr;

	for (auto session : _sessions)
		if (session->Info()->Id() == playerId)
			return session;

	return nullptr;
}

LobbySession::Ptr Lobby::FindSession(std::u16string nickname)
{
	if (nickname == std::u16string())
		return nullptr;

	std::u16string targetNickname = StringConverter::ToLowerCase(nickname);

	for (auto session : _sessions)
	{
		std::u16string possibleNickname = StringConverter::ToLowerCase(session->Info()->Nickname());

		if (possibleNickname == targetNickname)
			return session;
	}

	return nullptr;
}

void Lobby::SendPacket(ServerPacket pack)
{
	for (auto session : _sessions)
		session->Send(pack);
}

void Lobby::SendPacket(ServerPacket pack, uint32_t targetId)
{
	for (auto session : _sessions)
		if(session->Info()->Id() == targetId)
			return session->Send(pack);
}

void Lobby::Notify(std::u16string message)
{
	for (auto session : _sessions)
		session->Whisper(message);
}

bool Lobby::IsOnline(uint32_t playerId)
{
	auto session = FindSession(playerId);
	return session != nullptr ? true : false;
}

uint32_t Lobby::GetItemIdByCardId(uint32_t cardId)
{
	uint32_t itemId = 0;
	auto result = sDatabase->storeQuery(str(boost::format("SELECT item_id FROM player_items WHERE id = %1%") % cardId));
	if (result != nullptr)
		itemId =  result->getNumber<uint32_t>("item_id");

	return itemId;
}

void Lobby::SetAuthServer(std::shared_ptr<Connection> authServer)
{
	_authServer = authServer;
}

void Lobby::SetRoomServer(std::shared_ptr<Connection> conn)
{
	_roomServer = conn;
}

bool Lobby::ValidateNickname(std::u16string nickname)
{
	if (nickname.size() < 4 || nickname.size() > 16)
	{
		return false;
	}

	nickname = StringConverter::ToLowerCase(nickname);
	for (auto session : _sessions)
		if (StringConverter::ToLowerCase(session->Info()->Nickname()) == nickname)
			return true;

	std::string escapedNick = sDatabase->escapeString(StringConverter::Utf16ToUtf8(nickname));
	std::string query(str(boost::format("SELECT name FROM players WHERE name = %1%") % escapedNick));
	auto result = sDatabase->storeQuery(query);
	return result != nullptr ? true : false;
}

OfflinePlayer Lobby::ConstructOfflinePlayer(std::string query, OfflinePlayer::Type queryType)
{
	auto databaseResult = sDatabase->storeQuery(query);
	if (databaseResult != nullptr)
	{
		uint16_t character = databaseResult->getNumber<uint32_t>("default_character");
		uint32_t playerId = databaseResult->getNumber<uint32_t>("id");
		std::u16string nickname = StringConverter::Utf8ToUtf16(databaseResult->getString("name"));
		uint8_t rank = databaseResult->getNumber<uint32_t>("rank");
		uint8_t level = databaseResult->getNumber<uint32_t>("level");
		uint32_t experience = databaseResult->getNumber<uint32_t>("experience");
		uint32_t prestige = databaseResult->getNumber<uint32_t>("prestige");

		std::array<uint32_t, 13> equipment{};
		if (queryType >= OfflinePlayer::Type::MEDIUM)
		{
			databaseResult = sDatabase->storeQuery(str(boost::format("SELECT * FROM player_equipment WHERE player_id = %1% AND character_id = %2%") % playerId % character));

			if (databaseResult)
			{
				equipment[EquipmentManager::MELEE] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("melee"));
				equipment[EquipmentManager::PRIMARY] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("primary"));
				equipment[EquipmentManager::SECONDARY] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("secondary"));
				equipment[EquipmentManager::THROW] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("throw"));
				equipment[EquipmentManager::HEAD] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("head"));
				equipment[EquipmentManager::FACE] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("face"));
				equipment[EquipmentManager::BODY] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("body"));
				equipment[EquipmentManager::HAND] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("hands"));
				equipment[EquipmentManager::BOTTOM] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("legs"));
				equipment[EquipmentManager::FOOT] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("shoes"));
				equipment[EquipmentManager::BACK] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("back"));
				equipment[EquipmentManager::SIDE] = GetItemIdByCardId(databaseResult->getNumber<uint32_t>("side"));
			}
		}
		if (queryType >= OfflinePlayer::Type::MAXIMAL)
		{
			// Query more..
		}
		return OfflinePlayer{playerId, nickname, level, rank, experience, prestige, character, equipment };
	}
	else
	{
		return OfflinePlayer{};
	}
}
