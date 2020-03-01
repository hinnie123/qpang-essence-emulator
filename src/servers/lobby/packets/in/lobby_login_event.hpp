#ifndef LOBBY_LOGIN_EVENT_HPP
#define LOBBY_LOGIN_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_notify_event.hpp"
#include "lobby.hpp"

class LobbyLoginEvent : public LobbyPacketEvent {

public:
	LobbyLoginEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		std::array<uint8_t, 16> uuid = pack.ReadArray<uint8_t, 16>();
		pack.Skip(56);

		session->Info()->Uuid(uuid);

		auto authServer = session->GetLobby()->GetAuth();
		
		if(authServer)
			authServer->SendPacket(LobbyNotifyEvent{ uuid }.Compose(session));
	};
};

#endif