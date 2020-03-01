#ifndef CHANGE_PLAYER_STATE_EVENT_HPP
#define CHANGE_PLAYER_STATE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include <cstdint>

class ChangePlayerStateEvent : public SquarePacketEvent {

public:
	enum State : uint32_t {
		IDLE = 0,
		IN_GAME = 5,
		IN_TUTORIAL = 7,
	};

	ChangePlayerStateEvent(uint32_t playerId, uint32_t state) { _playerId = playerId; _state = state; };

	ServerPacket Compose(SquareSession* session) override {

		auto packet = ServerPacket::Create < Opcode::SQUARE_PLAYER_CHANGE_STATE>();

		packet.WriteInt(_playerId);
		packet.WriteInt(_state);
		packet.WriteInt(0); // unknown

		return packet;
	};
private:
	uint32_t _playerId;
	uint32_t _state;
};

#endif