#ifndef JOIN_EVENT_HPP
#define JOIN_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_manager.hpp"
#include "join_response_event.hpp"
#include <memory>

//THIS IS THE EVENT WHICH IS GETTING FIRED IF PLAYER WANTS TO JOIN A SQUARE.
class JoinEvent : public SquarePacketEvent {

public:
	JoinEvent() : SquarePacketEvent(sizeof(Packets::Square::ParkJoin)) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		uint32_t parkId = pack.ReadInt();
		uint32_t unknown01 = pack.ReadInt();
		
		std::shared_ptr<Square> square = session->GetSquare();

		if (square != nullptr)
		{
			if(square->Id() == parkId)
				return session->SendError<Opcode::SQUARE_JOIN_PARK_FAIL>(1403);

			square->RemovePlayer(session->Info()->Id());
			square = session->GetSquareManager()->GetSquare(parkId);
		}

		if (square == nullptr)
		{
			square = session->GetSquareManager()->GetAvailableSquare();
		}

		if (square->AddPlayer(session->GetSquareManager()->FindSession(session->Info()->Id())))
			session->Send(JoinResponseEvent{ square }.Compose(session));
		else
			return session->SendError<Opcode::SQUARE_JOIN_PARK_FAIL>(1403);
	}
};

#endif