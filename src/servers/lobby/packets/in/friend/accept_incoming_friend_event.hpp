#ifndef ACCEPT_INCOMING_FRIEND_EVENT_HPP
#define ACCEPT_INCOMING_FRIEND_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "accept_incoming_friend_response_event.hpp"
#include "friend_manager.hpp"
#include "friend.hpp"
#include "outgoing_friend_accepted_event.hpp"
#include "lobby.hpp"

class AcceptIncomingFriendEvent : public LobbyPacketEvent {

public:
	AcceptIncomingFriendEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::AcceptFriendRequest)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		pack.Skip(46);

		if (!session->Friends()->HasFriend(playerId))
			return;

		Friend theNewFriend = session->Friends()->AcceptFriend(playerId);
		auto target = session->GetLobby()->FindSession(playerId);

		if (target != nullptr)
		{
			Friend acceptedFriend = target->Friends()->AcceptFriend(session->Info()->Id());
			target->Send(OutgoingFriendAcceptedEvent{ acceptedFriend }.Compose(nullptr));
		}
		session->Send(AcceptIncomingFriendResponseEvent{ theNewFriend, target != nullptr }.Compose(session));
	}
};

#endif