#ifndef WHISPER_RESPONSE_EVENT_HPP
#define WHISPER_RESPONSE_EVENT_HPP

#include <memory>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"
#include <vector>
#include <cstdint>
#include <string>

class WhisperResponseEvent : public LobbyPacketEvent {

public:
	WhisperResponseEvent(std::u16string nickname, std::u16string message) { _nickname = nickname; _message = message; }

	ServerPacket Compose(LobbySession* session) override 
	{
		auto packet = ServerPacket::Create<Opcode::LOBBY_WHISPER_RSP>();

		packet.WriteInt(0); // unknown
		packet.WriteShort(_message.size());

		packet.WriteUtf16String(_nickname, 16);
		packet.WriteUtf16String(_message, 254);

		return packet;
	};

private:
	std::u16string _nickname;
	std::u16string _message;	
};

#endif