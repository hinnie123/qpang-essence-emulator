#ifndef JOIN_RESPONSE_EVENT_HPP
#define JOIN_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <memory>
#include "square.hpp"
#include "string_converter.hpp"

class JoinResponseEvent : public SquarePacketEvent {

public:
	JoinResponseEvent(Square::Ptr square) { _square = square; };

	ServerPacket Compose(SquareSession* session) override
	{
		Packets::Square::ParkJoinRsp rsp{};

		auto packet = ServerPacket::Create<Opcode::SQUARE_JOIN_PARK_RSP>();

		packet.WriteShort(_square->Id());
		packet.WriteEmpty(7);
		packet.WriteInt(_square->Id());
		packet.WriteByte(_square->MaxCapacity());
		packet.WriteByte(_square->List().size());
		packet.WriteByte(_square->State());
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_square->Name()), 16);
		packet.WriteEmpty(33);
		packet.WriteArray<float, 6>(std::array<float, 6>());

		return packet;
	}
private:
	Square::Ptr _square;
};

#endif