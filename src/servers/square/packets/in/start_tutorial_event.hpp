#ifndef START_TUTORIAL_EVENT_HPP
#define START_TUTORIAL_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"
#include "change_player_state_event.hpp"
#include <array>

class StartTutorialEvent : public SquarePacketEvent
{
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		auto square = session->GetSquare();
		if (square == nullptr) return;

		session->Info()->SetState(ChangePlayerStateEvent::IN_TUTORIAL);
		square->SendPacket(ChangePlayerStateEvent{ session->Info()->Id(), ChangePlayerStateEvent::IN_TUTORIAL }.Compose(nullptr));
	};
};


#endif // !UPDATE_PLAYER_EVENT_HPP
