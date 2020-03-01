#ifndef LOGIN_EVENT_HPP
#define LOGIN_EVENT_HPP

#include "square_packet_event.hpp"
#include "request_equipment_event.hpp"
#include "square_session.hpp"
#include "square_manager.hpp"

class LoginEvent : public SquarePacketEvent {

public:
	LoginEvent() : SquarePacketEvent(sizeof(Packets::Square::Login)) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		std::u16string nickname = pack.ReadUtf16String(16);
		pack.Skip(48);

		// TODO: Somehow confirm that this session actually belongs to this playerId

		session->SetPlayerId(playerId);
		auto lobby = session->GetSquareManager()->LobbyServer();

		lobby->SendPacket(RequestEquipmentEvent{ playerId }.Compose(session));
	}
};

#endif