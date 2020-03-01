#ifndef REMOVE_OUTGOING_FRIEND_EVENT_HPP
#define REMOVE_OUTGOING_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "remove_outgoing_friend_response_event.hpp"
#include "remove_incoming_friend_event.hpp"
#include "friend_manager.hpp"

class RemoveOutgoingFriendEvent : public LobbyPacketEvent {

public:
	RemoveOutgoingFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::RemoveOutgoingFriend)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();

		if (session->Info()->Id() == playerId)
			return;

		session->Friends()->RemoveFriend(playerId);

		auto target = session->GetLobby()->FindSession(playerId);

		if (target != nullptr)
		{
			target->Friends()->RemoveFriend(session->Info()->Id());
			target->Send(RemoveIncomingFriendEvent{ session->Info()->Id(), session->Info()->Nickname() }.Compose(nullptr));
		}

		session->Send(RemoveOutgoingFriendResponseEvent{ playerId }.Compose(session));
	}
};

#endif