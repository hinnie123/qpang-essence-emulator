#ifndef WHISPER_EVENT_HPP
#define WHISPER_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "lobby_session.hpp"
#include "string_converter.hpp"

#include "whisper_received_event.hpp"
#include "whisper_response_event.hpp"
#include "whisper_fail_event.hpp"
#include <string>

/// TODO: implement options
class WhisperEvent : public LobbyPacketEvent {

public:
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t unk01 = pack.ReadInt();
		uint16_t length = pack.ReadShort();
		std::u16string nickname = pack.ReadUtf16String(16);
		std::u16string message = pack.ReadUtf16String(length);

		auto target = session->GetLobby()->FindSession(nickname);

		if (target == nullptr)
			return session->Send(WhisperFailEvent{ 719 }.Compose(session));

		auto packet = WhisperReceivedEvent{ session->Info()->Nickname(), message };
		auto rspPacket = WhisperResponseEvent{ nickname, message };

		target->Send(packet.Compose(target.get()));
		session->Send(rspPacket.Compose(session));
	}
};

#endif