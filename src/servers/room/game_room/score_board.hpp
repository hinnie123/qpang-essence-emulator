#ifndef _SCORE_BOARD_HPP
#define _SCORE_BOARD_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <numeric>
#include <functional>

#include "team.hpp"


class ScoreBoard
{
public:

	struct Player {
		uint32_t id;
		uint32_t level;
		uint8_t team;
		std::string name;
		uint32_t kills;
		uint32_t deaths;
		uint32_t score;
	};


	ScoreBoard() = default;
	~ScoreBoard() = default;

	uint16_t GetBlueScore();
	uint16_t GetYellowscore();
	uint16_t GetValueLeader();

	void AddPlayer(ScoreBoard::Player player);
	std::vector<ScoreBoard::Player> GetResults();

private:
	std::vector<ScoreBoard::Player> m_players;
};

#endif // !_SCORE_BOARD_HPP
