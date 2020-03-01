#ifndef JOIN_BACK_RESPONSE_EVENT_HPP
#define JOIN_BACK_RESPONSE_EVENT_HPP


#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"
#include <array>

class JoinBackResponseEvent : public SquarePacketEvent {

public:
	JoinBackResponseEvent(std::array<float, 3> position) { _position = position; };

	ServerPacket Compose(SquareSession* session) override {

		auto packet = ServerPacket::Create<Opcode::SQUARE_JOIN_BACK_RSP>();

		packet.WriteArray<float, 3>(_position);

		return packet;
	};
private: 
	std::array<float, 3> _position;
};

#endif