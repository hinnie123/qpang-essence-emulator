#ifndef CHANNELS_RESPONSE_EVENT_HPP
#define CHANNELS_RESPONSE_EVENT_HPP

#include <memory>
#include <vector>
#include "channel.hpp"
#include "lobby_packet_event.hpp"
#include "packet_data.hpp"
#include "string_converter.hpp"

class ChannelsResponseEvent : public LobbyPacketEvent {

public:
	ChannelsResponseEvent(std::vector<Channel> channels) { _channels = channels; };

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::LOBBY_CHANNELS_RSP>();

		uint16_t size = _channels.size();

		packet.WriteShort(size);
		packet.WriteShort(size);
		packet.WriteShort(size);

		for (uint16_t i = 0; i < size; i++)
		{
			Channel channel = _channels.at(i);

			packet.WriteShort(i + 1);
			packet.WriteUtf16String(StringConverter::Utf8ToUtf16(channel.name), 30);
			packet.WriteByte(channel.minLevel);
			packet.WriteByte(channel.maxLevel);
			packet.WriteShort(channel.currPlayers);
			packet.WriteShort(channel.maxPlayers);
			packet.WriteEmpty(51);
		}

		return packet;
	};
private:
	std::vector<Channel> _channels;

};

#endif