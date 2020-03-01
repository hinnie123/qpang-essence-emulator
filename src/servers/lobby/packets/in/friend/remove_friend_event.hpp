#ifndef REMOVE_FRIEND_EVENT_HPP
#define REMOVE_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "friend_manager.hpp"
#include "friend.hpp"
#include "remove_friend_response_event.hpp"
#include "friend_removed_friend_event.hpp"

class RemoveFriendEvent : public LobbyPacketEvent {

public:
	RemoveFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::RemoveFriend)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		
		auto target = session->GetLobby()->FindSession(playerId);

		session->Friends()->RemoveFriend(playerId);
		if (target != nullptr)
		{
			target->Friends()->RemoveFriend(session->Info()->Id());
			target->Send(FriendRemovedFriendEvent{ session->Info()->Id(), session->Info()->Nickname() }.Compose(target.get()));
		}

		session->Send(RemoveFriendResponseEvent{ playerId }.Compose(session));
	}
};

#endif