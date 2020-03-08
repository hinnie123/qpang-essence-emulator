#ifndef REQUEST_AUTH_RESPONSE_EVENT_HPP
#define REQUEST_AUTH_RESPONSE_EVENT_HPP

#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include "string_converter.hpp"
#include "lobby_packet_event.hpp"

class RequestAuthResponseEvent : public LobbyPacketEvent {

public:
	RequestAuthResponseEvent(uint32_t cmd, uint32_t playerId) { _cmd = cmd; _playerId = playerId; };
	RequestAuthResponseEvent(uint32_t cmd, uint32_t playerId, std::u16string nickname, uint32_t experience, uint32_t prestige, uint8_t rank, uint8_t level, uint16_t characterId, uint32_t don, uint32_t cash, std::array<uint64_t, 13> cardIds, std::array<uint32_t, 13> itemIds)
	{
		_cmd = cmd;
		_playerId = playerId;
		_nickname = nickname;
		_experience = experience;
		_prestige = prestige;
		_rank = rank;
		_level = level;
		_characterId = characterId;
		_cardIds = cardIds;
		_itemIds = itemIds;
		_cash = cash;
		_don = don;
	}

	ServerPacket Compose(LobbySession* session) override {

		auto packet = ServerPacket::Create<Opcode::ROOM_REQUEST_AUTH_RSP>();

		packet.WriteInt(_playerId);
		packet.WriteInt(_cmd);
		packet.WriteUtf16String(_nickname, 16);
		packet.WriteShort(_characterId);
		packet.WriteByte(_level);
		packet.WriteInt(_experience);
		packet.WriteByte(_rank);
		packet.WriteShort(_prestige);
		packet.WriteInt(_don);
		packet.WriteInt(_cash);
		packet.WriteArray<uint64_t, 13>(_cardIds);
		packet.WriteArray<uint32_t, 13>(_itemIds);

		return packet;
	};

private:

	uint32_t _cmd;
	uint32_t _playerId;
	std::u16string _nickname;
	uint32_t _experience;
	uint32_t _prestige;
	uint8_t _rank;
	uint8_t _level;
	uint16_t _characterId;
	uint32_t _don;
	uint32_t _cash;

	std::array<uint64_t, 13> _cardIds;
	std::array<uint32_t, 13> _itemIds;
};

#endif