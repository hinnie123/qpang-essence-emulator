#ifndef MOVE_RESPONE_EVENT_HPP
#define MOVE_RESPONE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include "square.hpp"
#include <array>

class MoveResponseEvent : public SquarePacketEvent {

public:
	MoveResponseEvent(uint32_t playerId, std::array<float, 3> position, uint8_t moveType, uint8_t moveDirection)
	{
		_playerId = playerId;
		_position = position;
		_moveType = moveType;
		_moveDirection = moveDirection;
	}

	ServerPacket Compose(SquareSession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::SQUARE_MOVE_PLAYER>();

		packet.WriteInt(_playerId);
		packet.WriteByte(_moveType);
		packet.WriteByte(_moveDirection);
		packet.WriteArray<float, 3>(_position);

		return packet;
	};
private:
	uint32_t _playerId;
	std::array<float, 3> _position;
	uint8_t _moveType;
	uint8_t _moveDirection;
};

#endif