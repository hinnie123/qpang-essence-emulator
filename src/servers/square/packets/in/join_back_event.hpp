#ifndef JOIN_BACK_EVENT_HPP
#define JOIN_BACK_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"
#include "join_back_response_event.hpp"
#include "change_player_state_event.hpp"
#include <array>

class JoinBackEvent : public SquarePacketEvent
{
	void Read(SquareSession* session, ClientPacket& pack) override 
	{
		std::array<float, 3> position = session->Info()->Position();
		session->Info()->SetState(ChangePlayerStateEvent::IDLE);

		auto square = session->GetSquare();

		if (square == nullptr) return;

		square->SendPacket(ChangePlayerStateEvent{ session->Info()->Id(), ChangePlayerStateEvent::IDLE }.Compose(nullptr));

		session->Send(JoinBackResponseEvent{ position }.Compose(session));
	};
};


#endif // !UPDATE_PLAYER_EVENT_HPP
