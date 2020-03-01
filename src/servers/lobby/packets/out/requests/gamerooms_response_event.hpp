#ifndef GAMEROOMS_RESPONSE_EVENT_HPP
#define GAMEROOMS_RESPONSE_EVENT_HPP

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include <vector>
#include "gameroom.hpp"
#include "settings_manager.hpp"

class GameroomsResponseEvent : public LobbyPacketEvent {

public:	
	GameroomsResponseEvent(std::vector<GameRoom> rooms) { _rooms = rooms; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_GAMEROOMS_RSP>();

		packet.WriteShort(_rooms.size());
		packet.WriteShort(_rooms.size());
		packet.WriteShort(_rooms.size());

		Packets::Lobby::GameRoomList rsp{};

		for (size_t i = 0; i < _rooms.size(); i++)
		{
			auto& room = _rooms.at(i);

			packet.WriteInt(inet_addr(sSettings->GetSetting("room_host").c_str()));
			packet.WriteShort(boost::lexical_cast<uint16_t>(sSettings->GetSetting("room_port")));
			packet.WriteInt(room.id);
			packet.WriteEmpty(2);
			packet.WriteUtf16String(StringConverter::Utf8ToUtf16(room.name), 30);
			packet.WriteEmpty(14);
			packet.WriteByte(room.map);
			packet.WriteByte(room.mode);
			packet.WriteFlag(false); // password protected
			packet.WriteByte(room.state);
			packet.WriteByte(room.currPlayers);
			packet.WriteByte(room.maxPlayers);
			packet.WriteEmpty(5);
			packet.WriteFlag(false); // level limit
			packet.WriteFlag(false); // team sorting
			packet.WriteFlag(false); // skils enabled
			packet.WriteEmpty(5);
			packet.WriteFlag(false); // melee only
		}

		return packet;
	};
private:
	std::vector<GameRoom> _rooms;
};

#endif