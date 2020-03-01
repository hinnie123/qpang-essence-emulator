#ifndef OPEN_MEMO_EVENT_HPP
#define OPEN_MEMO_EVENT_HPP

#include <cstdint>
#include <memory>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"
#include "messenger_manager.hpp"
#include "lobby_session.hpp"
#include "lobby.hpp"
#include "message.hpp"

#include "open_memo_response_event.hpp"

class OpenMemoEvent : public LobbyPacketEvent {

public:
	OpenMemoEvent() : LobbyPacketEvent() {};
	void Read(LobbySession* session, ClientPacket& pack) override
	{
		uint64_t memoId = pack.ReadLong();
		uint32_t unk01 = pack.ReadInt();

		session->Messenger()->OpenMemo(memoId);
		session->Send(OpenMemoResponseEvent{ static_cast<uint32_t>(memoId) }.Compose(session));
	}
};

#endif