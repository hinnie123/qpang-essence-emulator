#include "score_board.hpp"

uint16_t ScoreBoard::GetBlueScore()
{
	uint16_t val = 0;

	for (ScoreBoard::Player player : m_players)
	{
		if (player.team == Team::BLUE)
			val += player.score;
	}

	return val;
}

uint16_t ScoreBoard::GetYellowscore()
{
	uint16_t val = 0;

	for (ScoreBoard::Player player : m_players)
	{
		if (player.team == Team::YELLOW)
			val += player.score;
	}

	return val;
}

uint16_t ScoreBoard::GetValueLeader()
{
	uint16_t val = 0;

	for (ScoreBoard::Player player : m_players)
	{
		if (player.score > val) {
			val = player.score;
		}
	}

	return val;
}

void ScoreBoard::AddPlayer(ScoreBoard::Player player)
{
	m_players.push_back(player);
}

std::vector<ScoreBoard::Player> ScoreBoard::GetResults()
{
	return m_players;
}
