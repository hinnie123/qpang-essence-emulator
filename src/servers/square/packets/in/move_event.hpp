#ifndef MOVE_EVENT_HPP
#define MOVE_EVENT_HPP

#include "square_packet_event.hpp"
#include "move_response_event.hpp"
#include "packet_data.hpp"

class MoveEvent : public SquarePacketEvent
{
public:
	MoveEvent() : SquarePacketEvent(22) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		uint8_t type = pack.ReadByte();
		uint8_t direction = pack.ReadByte();
		std::array<float, 3> position = pack.ReadArray<float, 3>();
		uint16_t unknown1 = pack.ReadShort();

		auto square = session->GetSquare();
		if (square == nullptr) return;

		session->Info()->SetPosition(position);
		square->SendPacket(MoveResponseEvent{ session->Info()->Id(), position, type, direction }.Compose(session));
	};
};


#endif // !MOVE_EVENT_HPP
