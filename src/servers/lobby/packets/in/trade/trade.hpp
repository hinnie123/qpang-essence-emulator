#ifndef TRADE_HPP
#define TRADE_HPP

#include <vector>
#include <unordered_map>

#include "lobby_session.hpp"

struct TradeInfo
{
	std::vector<uint64_t> proposedItems;
	LobbySession* tradingWith;
	bool didFinish;
};

extern std::unordered_map<uint32_t, TradeInfo> trades;

#endif