#include "channel_manager.hpp"

ChannelManager::ChannelManager()
{
	Load();
}

ChannelManager::~ChannelManager()
{
}

void ChannelManager::Load()
{
	_channels.clear();

	auto result = sDatabase->storeQuery("SELECT * FROM channels");
	if (result != nullptr)
	{
		do
		{
			std::string name = result->getString("name");
			std::string ipAddress = result->getString("ip");
			uint8_t minLevel = result->getNumber<uint32_t>("min_level");
			uint8_t maxLevel = result->getNumber<uint32_t>("max_level");
			uint8_t minRank = result->getNumber<uint32_t>("min_rank");
			uint8_t maxPlayers = result->getNumber<uint32_t>("max_players");
			_channels.push_back(Channel{ name, minLevel, maxLevel, minRank, 0, maxPlayers, ipAddress });
			result->next();
		} while (result->hasNext());
	}
}

Channel* ChannelManager::GetChannel(uint32_t channelIndex)
{
	channelIndex--;
	if (channelIndex >= _channels.size())
		return nullptr;

	return &_channels.at(channelIndex);
}

bool ChannelManager::AddPopulation(uint32_t channelIndex)
{
	auto channel = GetChannel(channelIndex);

	if (channel == nullptr) return false;

	if (channel->currPlayers >= channel->maxPlayers) return false;

	channel->currPlayers++;

	return true;
}

void ChannelManager::RemovePopulation(uint32_t channelIndex)
{
	auto channel = GetChannel(channelIndex);
	if (channel != nullptr) channel->currPlayers--;
}

std::vector<Channel> ChannelManager::List()
{
	return _channels;
}
