#ifndef CHANNEL_CONNECT_RESPONSE_EVENT_HPP
#define CHANNEL_CONNECT_RESPONSE_EVENT_HPP

#include <cstdint>

#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "channel.hpp"
#include "lobby.hpp"
#include "channel_manager.hpp"

class ChannelConnectResponseEvent : public LobbyPacketEvent {

public:
	ChannelConnectResponseEvent(Channel channel, uint32_t index) { _channel = channel; _index = index; };

	ServerPacket Compose(LobbySession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::LOBBY_CHANNEL_CONNECT_RSP>();

		packet.WriteInt(_index);
		packet.WriteLong(0);
		packet.WriteInt(_channel.ipAddress);
		packet.WriteInt(0);
		packet.WriteInt(0);
		packet.WriteInt(0);

		return packet;
	};
private:
	Channel _channel;
	uint32_t _index;
};

#endif