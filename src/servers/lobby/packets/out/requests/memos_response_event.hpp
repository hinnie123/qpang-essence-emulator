#ifndef MEMOS_RESPONSE_EVENT_HPP
#define MEMOS_RESPONSE_EVENT_HPP

#include <memory>

#include <cstdint>
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "message.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"

class MemosResponseEvent : public LobbyPacketEvent {

public:
	MemosResponseEvent(std::vector<Message> messages) { _messages = messages; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_MEMOS_RSP>();

		packet.WriteShort(_messages.size());
		packet.WriteShort(_messages.size());
		packet.WriteShort(_messages.size());

		for (int32_t i = 0; i < _messages.size(); i++)
		{
			if (i >= MAX_MESSAGES)
				break;

			Message message = _messages.at(i);

			packet.WriteLong(message.id);
			packet.WriteInt(message.senderId);
			packet.WriteInt(message.received);
			packet.WriteUtf16String(StringConverter::Utf8ToUtf16(message.senderName), 16);
			packet.WriteUtf16String(StringConverter::Utf8ToUtf16(message.messageBody), 100);
			packet.WriteFlag(message.opened);
		}

		return packet;
	};
private:
	std::vector<Message> _messages;
};

#endif