#include "friend_manager.hpp"

void FriendManager::Load(uint32_t playerId)
{
	std::string query = "SELECT * FROM friends JOIN players ON players.id = friends.player_to WHERE friends.player_from = %1%";
	auto result = sDatabase->storeQuery(str(boost::format(query) % playerId));

	if (result != nullptr)
	{
		do
		{
			uint32_t id = result->getNumber<uint32_t>("id");
			uint32_t fromPlayerId = result->getNumber<uint32_t>("player_from");
			uint32_t toPlayerId = result->getNumber<uint32_t>("player_to");
			std::u16string fromPlayerNickname = StringConverter::Utf8ToUtf16(result->getString("name"));
			uint8_t level = result->getNumber<uint32_t>("level");
			uint8_t friendshipState = result->getNumber<uint32_t>("status");

			_friends.push_back(Friend{id, fromPlayerId, toPlayerId, fromPlayerNickname, level, friendshipState});
			result->next();
		} while (result->hasNext());
	}
}

std::vector<Friend> FriendManager::List()
{
	return _friends;
}

Friend FriendManager::ConstructFriend(uint32_t fromId, uint32_t friendPlayerId, std::u16string nickname, uint8_t level)
{
	return Friend{ 0, fromId, friendPlayerId, nickname, level, 0 };
}

bool FriendManager::HasFriend(uint32_t playerId)
{
	for (Friend theFriend : _friends)
		if (theFriend.toPlayerId == playerId)
			return true;

	return false;
}

bool FriendManager::HasFriend(std::u16string username)
{
	for (Friend theFriend : _friends)
		if (StringConverter::ToLowerCase(theFriend.nickname) == StringConverter::ToLowerCase(username))
			return true;

	return false;
}

bool FriendManager::AddFriend(Friend friendToAdd, State state)
{
	if (HasFriend(friendToAdd.nickname))
		return false;

	if (_friends.size() >= MAX_FRIENDS)
		return false;

	bool result;

	//TODO: Put this somewhere else?
	if (state != State::BOTH)
	{
		friendToAdd.state = static_cast<uint8_t>(state);
		result = sDatabase->executeQuery(str(boost::format("INSERT INTO friends (player_from, player_to, status) VALUES (%1%, %2%, %3%)") % friendToAdd.fromId % friendToAdd.toPlayerId % state));
	}
	else
	{
		result = sDatabase->executeQuery(str(boost::format("INSERT INTO friends (player_from, player_to, status) VALUES (%1%, %2%, %3%)") % friendToAdd.fromId % friendToAdd.toPlayerId % State::OUTGOING));
		sDatabase->executeQuery(str(boost::format("INSERT INTO friends (player_from, player_to, status) VALUES (%1%, %2%, %3%)") % friendToAdd.toPlayerId % friendToAdd.fromId % State::INCOMING));
		friendToAdd.state = static_cast<uint8_t>(State::OUTGOING);
	}

	if(result)
		_friends.push_back(friendToAdd);

	return result;
}

Friend FriendManager::AcceptFriend(uint32_t friendId)
{
	if (HasFriend(friendId))
	{
		for (auto it = _friends.begin(); it != _friends.end(); it++)
		{
			if (it->toPlayerId == friendId)
			{
				sDatabase->executeQuery(str(boost::format("UPDATE friends SET status = 1 WHERE (user_from = %1% AND user_to = %2% ) OR (user_from = %2% AND user_to = %1% )") % it->toPlayerId % it->fromId));
				it->state = State::FRIENDS;
				return *it;
			}
		}
	}
}

bool FriendManager::RemoveFriend(uint32_t targetId)
{
	if (HasFriend(targetId))
	{
		for (auto it = _friends.begin(); it != _friends.end(); it++)
		{
			if (it->toPlayerId == targetId)
			{
				bool result = sDatabase->executeQuery(str(boost::format("DELETE FROM friends WHERE (player_from = %1% AND player_to = %2%) OR (player_from = %2% AND player_to = %1%)") % it->toPlayerId % it->fromId));
				_friends.erase(it);
				return result;
			}
		}
	}
	return false;
}

void FriendManager::SendPacket(ServerPacket& pack, std::shared_ptr<Lobby> lobby)
{
	for (Friend theFriend : _friends)
	{
		lobby->SendPacket(pack, theFriend.id);
	}
}
