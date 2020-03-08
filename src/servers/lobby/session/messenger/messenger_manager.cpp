#include "messenger_manager.hpp"
#include "string_converter.hpp"


void MessengerManager::Load(uint32_t playerId)
{
	std::string query = "SELECT memos.id, memos.sender_id, memos.message, players.name, memos.opened, memos.created FROM memos JOIN players ON players.id = memos.sender_id WHERE receiver_id = %1%";
	auto result = sDatabase->storeQuery(str(boost::format(query) % playerId));

	if (result)
	{
		do
		{
			uint32_t id = result->getNumber<uint32_t>("id");
			uint32_t senderId = result->getNumber<uint32_t>("sender_id");
			std::u16string senderName = StringConverter::Utf8ToUtf16(result->getString("name"));
			std::u16string message = StringConverter::Utf8ToUtf16(result->getString("message"));
			uint32_t created = result->getNumber<uint32_t>("created");
			uint8_t opened = result->getNumber<uint32_t>("opened");

			_messages.push_back(Message{id, senderId, senderName, message, created, opened});
			result->next();
		} while (result->hasNext());
	}
}

Message MessengerManager::ReceiveMemo(uint32_t fromId, uint32_t targetId, std::u16string nickname , std::u16string message)
{
	std::string escMessage = sDatabase->escapeString(StringConverter::Utf16ToUtf8(message));

	std::string query = str(boost::format("INSERT INTO memos (sender_id, receiver_id, message, created, opened) VALUES (%1%, %2%, %3%, %4%, %5%)")
	% fromId % targetId % escMessage % time(NULL) % 0 );
	bool result = sDatabase->executeQuery(query);
	if (result)
	{
		Message newMessage{ static_cast<uint32_t>(sDatabase->getLastInsertId()), fromId, nickname, message, static_cast<uint32_t>(time(NULL)), 0 };
		newMessage.id = sDatabase->getLastInsertId();
		newMessage.senderId = fromId;
		AddMemo(newMessage);
		return newMessage;
	}
	return Message{};
}

void MessengerManager::AddMemo(Message message)
{
	_messages.push_back(message);
}

void MessengerManager::OpenMemo(uint32_t memoId)
{
	for (auto it = _messages.begin(); it != _messages.end(); it++)
	{
		if (it->id == memoId)
		{
			it->opened = true;
			sDatabase->executeQuery(str(boost::format("UPDATE memos SET opened = 1 WHERE id = %1%") % it->id));
			return;
		}
	}
}

bool MessengerManager::RemoveMemo(uint32_t memoId)
{
	for (auto it = _messages.begin(); it != _messages.end(); it++)
	{
		if (it->id == memoId)
		{
			sDatabase->executeQuery(str(boost::format("DELETE FROM memos WHERE id = %1%") % it->id));
			_messages.erase(it);
			return true;
		}
	}
	return false;
}

std::vector<Message> MessengerManager::List()
{
	return _messages;
}
