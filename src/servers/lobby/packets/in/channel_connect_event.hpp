#ifndef CHANNEL_CONNECT_EVENT_HPP
#define CHANNEL_CONNECT_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "lobby.hpp"
#include "lobby_session.hpp"
#include "channel_connect_response_event.hpp"
#include "friend_manager.hpp"
#include "set_online_event.hpp"

class ChannelConnectEvent : public LobbyPacketEvent {

public:
	ChannelConnectEvent() : LobbyPacketEvent() {};

	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t channelId = pack.ReadInt();
		uint32_t unk01 = pack.ReadInt();
		uint32_t unk02 = pack.ReadInt();
		uint32_t unk03 = pack.ReadInt();
		uint32_t unk04 = pack.ReadInt();
		uint32_t unk05 = pack.ReadInt();

		if (session->GetLobby()->Channels()->GetChannel(session->Info()->Channel()) != nullptr)
			session->GetLobby()->Channels()->RemovePopulation(session->Info()->Channel());

		Channel channel = *(session->GetLobby()->Channels()->GetChannel(channelId));
		if (!session->GetLobby()->Channels()->AddPopulation(channelId) || channelId == NULL)
			return session->SendError<Opcode::LOBBY_SERVER_ERROR>(852);

		session->Info()->Channel(channelId);

		auto onlineEvent = SetOnlineEvent{ session->Info()->Id() }.Compose(session);
		session->Friends()->SendPacket(onlineEvent, session->GetLobby());
		session->Send(ChannelConnectResponseEvent{ channel, channelId }.Compose(session));
	};
};

#endif