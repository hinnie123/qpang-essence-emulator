#ifndef DENY_INCOMING_FRIEND_EVENT_HPP
#define DENY_INCOMING_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "friend_manager.hpp"
#include "friend.hpp"
#include "outgoing_friend_denied_event.hpp"
#include "deny_incoming_friend_response_event.hpp"

class DenyIncomingFriendEvent : public LobbyPacketEvent {

public:
	DenyIncomingFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::DenyFriendRequest)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		pack.Skip(46);

		if (!session->Friends()->HasFriend(playerId))
			return;

		session->Friends()->RemoveFriend(playerId);
		auto target = session->GetLobby()->FindSession(playerId);

		if (target != nullptr)
		{
			target->Friends()->RemoveFriend(session->Info()->Id());
			target->Send(OutgoingFriendDeniedEvent{ session->Info()->Id(), session->Info()->Nickname() }.Compose(target.get()));
		}

		session->Send(DenyIncomingFriendResponseEvent{ playerId }.Compose(session));
	}
};

#endif