#include "equipment_manager.hpp"
#include <boost/format.hpp>

EquipmentManager::EquipmentManager()
{
}

EquipmentManager::~EquipmentManager()
{
}

void EquipmentManager::Load(uint32_t playerId)
{
	auto result = sDatabase->storeQuery(str(boost::format("SELECT * FROM player_equipment WHERE player_id = %1%") % playerId));
	if (result != nullptr)
	{
		do
		{
			uint32_t index = GetCharacterIndex(result->getNumber<uint32_t>("character_id"));
			SetEquipmentPart((Character)index, EquipmentSlot::HEAD, result->getNumber<uint32_t>("head"));
			SetEquipmentPart((Character)index, EquipmentSlot::FACE, result->getNumber<uint32_t>("face"));
			SetEquipmentPart((Character)index, EquipmentSlot::BODY, result->getNumber<uint32_t>("body"));
			SetEquipmentPart((Character)index, EquipmentSlot::HAND, result->getNumber<uint32_t>("hands"));
			SetEquipmentPart((Character)index, EquipmentSlot::BOTTOM, result->getNumber<uint32_t>("legs"));
			SetEquipmentPart((Character)index, EquipmentSlot::FOOT, result->getNumber<uint32_t>("shoes"));
			SetEquipmentPart((Character)index, EquipmentSlot::BACK, result->getNumber<uint32_t>("back"));
			SetEquipmentPart((Character)index, EquipmentSlot::SIDE, result->getNumber<uint32_t>("side"));
			SetEquipmentPart((Character)index, EquipmentSlot::MELEE, result->getNumber<uint32_t>("melee"));
			SetEquipmentPart((Character)index, EquipmentSlot::PRIMARY, result->getNumber<uint32_t>("primary"));
			SetEquipmentPart((Character)index, EquipmentSlot::SECONDARY, result->getNumber<uint32_t>("secondary"));
			SetEquipmentPart((Character)index, EquipmentSlot::THROW, result->getNumber<uint32_t>("throw"));

			result->next();
		} while (result->hasNext());
	}
	else
	{
		for (size_t i = 0; i < _equipment.size(); i++)
		{
			for (size_t y = 0; y < _equipment[i].size(); y++)
			{
				_equipment[i][y] = 0;
			}
		}
	}
}

void EquipmentManager::Save(uint32_t playerId)
{
	std::string query;

	for (size_t i = 0; i < _equipment.size(); i++)
	{
		query = std::string();
		std::array<uint64_t, 13> characterEquipment = _equipment[i];
		query += "UPDATE player_equipment SET "
			" `melee` = " + sDatabase->validateValue(characterEquipment[MELEE]) + ", "
			" `primary` = " + sDatabase->validateValue(characterEquipment[PRIMARY]) + ", "
			" `secondary` = " + sDatabase->validateValue(characterEquipment[SECONDARY]) + ", "
			" `throw` = " + sDatabase->validateValue(characterEquipment[THROW]) + ", "
			" `head` = " + sDatabase->validateValue(characterEquipment[HEAD]) + ", "
			" `face` = " + sDatabase->validateValue(characterEquipment[FACE]) + ", "
			" `body` = " + sDatabase->validateValue(characterEquipment[BODY]) + ", "
			" `hands` = " + sDatabase->validateValue(characterEquipment[HAND]) + ", "
			" `legs` = " + sDatabase->validateValue(characterEquipment[BOTTOM]) + ", "
			" `shoes` = " + sDatabase->validateValue(characterEquipment[FOOT]) + ", "
			" `back` = " + sDatabase->validateValue(characterEquipment[BACK]) + ", "
			" `side` = " + sDatabase->validateValue(characterEquipment[SIDE]) + " "
			;
		query += " WHERE (player_id, character_id) IN ((" + std::to_string(playerId) + ", " + std::to_string(GetCharacterCode(i)) + "))";
		sDatabase->executeQuery(query);
	}
}

void EquipmentManager::SetEquipmentPart(Character character, EquipmentSlot slot, uint64_t cardId)
{
	_equipment[character][slot] = cardId;
}

uint64_t EquipmentManager::GetEquipmentPart(Character character, EquipmentSlot slot)
{
	return _equipment[character][slot];
}

uint16_t EquipmentManager::GetCharacterCode(uint32_t characterIndex)
{
	return _characters.find((Character)characterIndex)->second;
}

uint32_t EquipmentManager::GetCharacterIndex(uint32_t characterCode)
{
	for (auto set : _characters)
	{
		if (set.second == characterCode)
			return set.first;
	}

	return 0;
}

bool EquipmentManager::ValidateCharacter(uint16_t characterCode)
{
	for (auto& entry : _characters)
		if (entry.second == characterCode)
			return true;
	return false;
}

std::array<uint64_t, 9> EquipmentManager::GetArmor(Character character)
{
	std::array<uint64_t, 9> armor = 
	{
		_equipment[character][EquipmentSlot::HEAD],
		_equipment[character][EquipmentSlot::FACE],
		_equipment[character][EquipmentSlot::BODY],
		_equipment[character][EquipmentSlot::HAND],
		_equipment[character][EquipmentSlot::BOTTOM],
		_equipment[character][EquipmentSlot::FOOT],
		_equipment[character][EquipmentSlot::BACK],
		_equipment[character][EquipmentSlot::SIDE],
		_equipment[character][EquipmentSlot::UNKNOWN],
	};
	return armor;
}

std::array<uint64_t, 4> EquipmentManager::GetWeapons(Character character)
{
	std::array<uint64_t, 4> weapons =
	{
		_equipment[character][EquipmentSlot::PRIMARY],
		_equipment[character][EquipmentSlot::SECONDARY],
		_equipment[character][EquipmentSlot::THROW],
		_equipment[character][EquipmentSlot::MELEE],
	};
	return weapons;
}

std::array<uint64_t, 13> EquipmentManager::GetAllByCharacter(Character character)
{
	return _equipment[character];
}

std::array<std::array<uint32_t, 3>, 6> EquipmentManager::GetSkillCards()
{
	return _skillCards;
}

std::array<uint32_t, 3> EquipmentManager::GetSkillCardsByCharacter(Character character)
{
	return _skillCards[character];
}

std::array<std::array<uint64_t, 13>, 6> EquipmentManager::GetAll()
{
	return _equipment;
}



