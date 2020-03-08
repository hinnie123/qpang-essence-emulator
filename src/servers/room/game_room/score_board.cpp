#include "score_board.hpp"

ScoreBoard::ScoreBoard(uint16_t blueScore, uint16_t yellowScore, uint16_t scoreLeader, std::vector<ScoreBoard::Player> players)
	:
	m_blueScore(blueScore),
	m_yellowScore(yellowScore),
	m_scoreLeader(scoreLeader),
	m_players(players)
{
}

uint16_t ScoreBoard::GetBlueScore()
{
	return m_blueScore;
}

uint16_t ScoreBoard::GetYellowscore()
{
	return m_yellowScore;
}

uint16_t ScoreBoard::GetValueLeader()
{
	return m_scoreLeader;
}

void ScoreBoard::AddPlayer(ScoreBoard::Player player)
{
	m_players.push_back(player);
}

std::vector<ScoreBoard::Player> ScoreBoard::GetResults()
{
	return m_players;
}
