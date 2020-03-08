#include "team_death_match.hpp"
#include "game_room.hpp"

void FreeForAll::OnPlayerKill(const std::shared_ptr<GameRoomSession>& roomSession, const Player::Ptr & killer, const Player::Ptr & target)
{
	killer->GetSession()->AddScore();
	roomSession->AddScore(killer->GetTeam());

	Parent::OnPlayerKill(roomSession, killer, target);
}

void FreeForAll::OnApply(const std::shared_ptr<GameRoom>& room)
{
	room->BalancePlayers();
}

bool FreeForAll::IsTeamMode()
{
	return false;
}

std::string FreeForAll::GetName()
{
	return "Free For All";
}

uint8_t FreeForAll::GetModeIdentifier()
{
	return Mode::DEATH_MATCH;
}
