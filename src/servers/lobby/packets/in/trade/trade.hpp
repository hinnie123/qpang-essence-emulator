#ifndef TRADE_HPP
#define TRADE_HPP

#include <vector>
#include <unordered_map>

struct TradeInfo
{
	std::vector<uint64_t> proposedItems;
	bool didFinish;
};

extern std::unordered_map<uint32_t, TradeInfo> trades;

#endif