#ifndef SEND_MEMO_EVENT_HPP
#define SEND_MEMO_EVENT_HPP

#include <memory>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "message.hpp"
#include "send_memo_response_event.hpp"
#include "receive_memo_event.hpp"

class SendMemoEvent : public LobbyPacketEvent {

	enum Error {
		TARGET_CANNOT_RECEIVE_MEMO = 840,
		CANNOT_SEND_MEMO_MORE = 842,
		TARGET_NOT_ALLOW_MEMO = 843,
	};

public:
	SendMemoEvent() : LobbyPacketEvent(sizeof(Packets::Lobby::SendMemo)) {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint32_t playerId = pack.ReadInt();
		std::u16string nickname = pack.ReadUtf16String(16);
		std::u16string message = pack.ReadUtf16String(100);
		uint32_t unknown01 = pack.ReadInt();
		
		if (!session->GetLobby()->ValidateNickname(nickname))
			return session->SendError<Opcode::LOBBY_SEND_MEMO_FAIL>(Error::TARGET_CANNOT_RECEIVE_MEMO);

		auto target = session->GetLobby()->FindSession(nickname);

		if (target != nullptr)
		{
			Message memo = target->Messenger()->ReceiveMemo(session->Info()->Id(), target->Info()->Id(), session->Info()->Nickname(), message);

			if(memo.id == NULL)
				return session->SendError<Opcode::LOBBY_SEND_MEMO_FAIL>(Error::TARGET_CANNOT_RECEIVE_MEMO);

			target->Send(ReceiveMemoEvent{ memo }.Compose(session));
			session->Send(SendMemoResponseEvent{ 20 }.Compose(session));
		}
		else
		{
			//
		}
	}
};

#endif