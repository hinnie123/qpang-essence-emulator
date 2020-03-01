#ifndef UPDATE_LIST_EVENT_HPP
#define UPDATE_LIST_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include <cstdint>
#include "square.hpp"
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class UpdateListEvent : public SquarePacketEvent {

public:
	enum CMD : uint8_t {
		UPDATE = 0,
		REMOVE = 1,
	};

	UpdateListEvent(Square::Ptr square, CMD command) { _square = square; _command = command; };

	ServerPacket Compose(SquareSession* session) override
	{
		auto packet = ServerPacket::Create< Opcode::SQUARE_UPDATE_LIST>();

		packet.WriteInt(_command);
		packet.WriteEmpty(5);
		packet.WriteInt(_square->Id());
		packet.WriteByte(_square->MaxCapacity());
		packet.WriteByte(_square->List().size());
		packet.WriteByte(_square->State());
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_square->Name()), 16);
		packet.WriteEmpty(33);

		return packet;
	}
private:
	Square::Ptr _square;
	CMD _command;
};

#endif