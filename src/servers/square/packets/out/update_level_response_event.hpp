#ifndef UPDATE_LEVEL_RESPONSE_EVENT_HPP
#define UPDATE_LEVEL_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square.hpp"
#include <memory>
#include <vector>
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class UpdateLevelResponseEvent : public SquarePacketEvent {

public:
	UpdateLevelResponseEvent(uint32_t playerId, uint32_t level)
	{
		_playerId = playerId;
		_level = level;
	}

	ServerPacket Compose(SquareSession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::SQUARE_PLAYER_CHANGE_LEVEL>();

		packet.WriteInt(_playerId);
		packet.WriteShort(_level);

		return packet;
	}
private:
	uint32_t _playerId;
	uint16_t _level;
};

#endif