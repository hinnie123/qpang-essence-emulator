#ifndef PLAYER_JOIN_RESPONSE_EVENT_HPP
#define PLAYER_JOIN_RESPONSE_EVENT_HPP

#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square.hpp"
#include <memory>
#include <vector>
#include "info_manager.hpp"
#include "square_session.hpp"
#include "string_converter.hpp"

class PlayerJoinResponseEvent : public SquarePacketEvent {

public:
	PlayerJoinResponseEvent(std::vector<std::shared_ptr<SquareSession>> sessions) { _sessions = sessions; };

	ServerPacket Compose(SquareSession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::SQUARE_LOAD_PLAYERS>();
		uint32_t size = _sessions.size();

		packet.WriteShort(size);
		packet.WriteShort(size);
		packet.WriteShort(size); // minus ourself ? 

		for (SquareSession::Ptr target : _sessions)
		{
			packet.WriteInt(target->Info()->State());
			packet.WriteInt(target->Info()->Id());
			packet.WriteUtf16String(StringConverter::Utf8ToUtf16(target->Info()->Nickname()), 16);
			packet.WriteByte(target->Info()->Level());
			packet.WriteByte(target->Info()->Rank());
			packet.WriteShort(target->Info()->Prestige());
			packet.WriteShort(target->Info()->Character());
			packet.WriteArray<uint32_t, 9>(target->Info()->Equipment());
			packet.WriteEmpty(6);
			packet.WriteArray<float, 3>(target->Info()->Position());
		}

		return packet;
	}
private:
	std::vector<std::shared_ptr<SquareSession>> _sessions;
};

#endif