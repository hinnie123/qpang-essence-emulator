#include "info_manager.hpp"

#include "string_converter.hpp"

InfoManager::InfoManager()
{
}

InfoManager::~InfoManager()
{
}

void InfoManager::Load(uint32_t userId)
{
	Uid(userId);

	auto result = sDatabase->storeQuery(str(boost::format("SELECT * FROM players WHERE user_id = %1%") % std::to_string(userId)).c_str());
	if (result != nullptr)
	{
		_playerId = result->getNumber<uint32_t>("id");
		_nickname = StringConverter::Utf8ToUtf16(result->getString("name"));
		_rank = result->getNumber<uint32_t>("rank");
		_character = result->getNumber<uint32_t>("default_character");
		_level = result->getNumber<uint32_t>("level");
		_experience = result->getNumber<uint32_t>("experience");
		_prestige = result->getNumber<uint32_t>("prestige");
		_don = result->getNumber<uint32_t>("don");
		_cash = result->getNumber<uint32_t>("cash");
		_coins = result->getNumber<uint32_t>("coins");
	}
	else
		_playerId = userId;
}

std::array<uint8_t, 16> InfoManager::Uuid(std::array<uint8_t, 16> uuid)
{
	return _uuid = uuid;
}

std::u16string InfoManager::Nickname(std::u16string nickname)
{
	sDatabase->executeQuery(str(boost::format("UPDATE players SET name = %1% WHERE id = %2%") % sDatabase->escapeString(StringConverter::Utf16ToUtf8(nickname)) % Id()));
	return _nickname = nickname;
}

uint16_t InfoManager::Level(uint16_t level)
{
	ExecuteQuery(str(boost::format("UPDATE players SET level = %1% WHERE id = %2%") % level % Id()));
	return _level = level;
}

uint32_t InfoManager::Experience(uint32_t experience)
{
	ExecuteQuery(str(boost::format("UPDATE players SET experience = %1% WHERE id = %2%") % experience % Id()));
	return _experience = experience;
}

uint8_t InfoManager::Rank(uint8_t rank)
{
	ExecuteQuery(str(boost::format("UPDATE players SET rank = %1% WHERE id = %2%") % rank % Id()));
	return _rank = rank;
}

uint32_t InfoManager::Prestige(uint32_t prestige)
{
	ExecuteQuery(str(boost::format("UPDATE players SET prestige = %1% WHERE id = %2%") % prestige % Id()));
	return _prestige = prestige;
}

uint16_t InfoManager::Character(uint16_t character)
{
	ExecuteQuery(str(boost::format("UPDATE players SET default_character = %1% WHERE id = %2%") % character % Id()));
	return _character = character;
}

uint32_t InfoManager::Don(uint32_t don)
{
	ExecuteQuery(str(boost::format("UPDATE players SET don = %1% WHERE id = %2%") % don % Id()));
	return _don = don;
}

uint32_t InfoManager::Cash(uint32_t cash)
{
	ExecuteQuery(str(boost::format("UPDATE players SET cash = %1% WHERE id = %2%") % cash % Id()));
	return _cash = cash;
}

uint32_t InfoManager::Coins(uint32_t coins)
{
	ExecuteQuery(str(boost::format("UPDATE players SET coins = %1% WHERE id = %2%") % coins % Id()));
	return _coins = coins;
}

uint16_t InfoManager::Channel(uint16_t channelId)
{
	return _channelId = channelId;
}

uint32_t InfoManager::Uid(uint32_t uid)
{
	return _uid = uid;
}

void InfoManager::ExecuteQuery(std::string query)
{
	sDatabase->executeQuery(query);
}
