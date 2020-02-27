#ifndef OUTGOING_FRIEND_DENIED_EVENT_HPP
#define OUTGOING_FRIEND_DENIED_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include "friend.hpp"
#include <cstdint>
#include "string_converter.hpp"
#include "friend_manager.hpp"

class OutgoingFriendDeniedEvent : public LobbyPacketEvent {

public:
	OutgoingFriendDeniedEvent(uint32_t playerId, std::string nickname) { _playerId = playerId; _nickname = nickname; };

	ServerPacket Compose(LobbySession* session) override {
		auto packet = ServerPacket::Create<Opcode::LOBBY_OUTGOING_FRIEND_DENIED>();

		packet.WriteInt(_playerId);
		packet.WriteLong(0); // unknown
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_nickname), 16);

		return packet;
	};
private:
	uint32_t _playerId;
	std::string _nickname;
};

#endif