#ifndef REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP
#define REQUEST_EQUIPMENT_RESPONSE_EVENT_HPP

#include <array>
#include <string>
#include <cstdint>
#include "lobby_packet_event.hpp"
#include "string_converter.hpp"

class RequestEquipmentResponseEvent : public LobbyPacketEvent {

public:
	RequestEquipmentResponseEvent(std::array<uint32_t, 9> items, uint32_t playerId, uint8_t status, uint16_t level, uint8_t rank, uint16_t character, uint32_t prestige, std::u16string nickname)
	{
		_items = items;
		_playerId = playerId;
		_status = status;
		_level = level;
		_rank = rank;
		_character = character;
		_prestige = prestige;
		_nickname = nickname;
	};

	RequestEquipmentResponseEvent(bool status) { _status = status; };

	ServerPacket Compose(LobbySession* session) override
	{
		auto packet = ServerPacket::Create<Opcode::REQUEST_EQUIPMENT_RSP>();

		packet.WriteInt(_playerId);
		packet.WriteByte(_rank);
		packet.WriteShort(_level);
		packet.WriteShort(_character);
		packet.WriteInt(_prestige);
		packet.WriteFlag(_status);
		packet.WriteUtf16String(_nickname, 16);
		packet.WriteArray<uint32_t, 9>(_items);

		return packet;
	}
private:
	std::array<uint32_t, 9> _items;
	std::u16string _nickname;
	uint32_t _playerId;
	uint8_t _status;
	uint16_t _level;
	uint8_t _rank;
	uint16_t _character;
	uint32_t _prestige;
};

#endif