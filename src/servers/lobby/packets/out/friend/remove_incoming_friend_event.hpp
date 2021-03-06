#ifndef REMOVE_INCOMING_FRIEND_EVENT_HPP
#define REMOVE_INCOMING_FRIEND_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <string>
#include <cstdint>
#include "string_converter.hpp"

class RemoveIncomingFriendEvent : public LobbyPacketEvent {

public:
	RemoveIncomingFriendEvent(uint32_t targetId, std::string nickname) { _targetId = targetId; _nickname = nickname; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_REMOVE_INCOMING_FRIEND>();
	
		packet.WriteInt(_targetId);
		packet.WriteLong(0); // unknown
		packet.WriteUtf16String(StringConverter::Utf8ToUtf16(_nickname), 16);

		return packet;
	};
private:
	uint32_t _targetId;
	std::string _nickname;
};

#endif