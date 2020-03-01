#ifndef ADD_PLAYER_EVENT_HPP
#define ADD_PLAYER_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include <array>
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class AddPlayerEvent : public SquarePacketEvent {

public:
	ServerPacket Compose(SquareSession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::SQUARE_ADD_PLAYER>();

		packet.WriteInt(0); // ?
		packet.WriteInt(session->Info()->Id());
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(session->Info()->Nickname()), 16);
		packet.WriteByte(session->Info()->Level());
		packet.WriteByte(session->Info()->Rank());
		packet.WriteEmpty(2);
		packet.WriteShort(session->Info()->Character());
		packet.WriteArray<uint32_t, 9>(session->Info()->Equipment());
		packet.WriteEmpty(4);
		packet.WriteArray<float, 3>(session->Info()->Position());

		return packet;
	}
private:
};

#endif