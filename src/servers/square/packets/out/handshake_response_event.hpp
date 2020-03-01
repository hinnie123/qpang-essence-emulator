#ifndef HANDSHAKE_RESPONSE_EVENT_HPP
#define HANDSHAKE_RESPONSE_EVENT_HPP


#include "square_packet_event.hpp"
#include "packet_data.hpp"
#include "square_session.hpp"

class HandshakeResponseEvent : public SquarePacketEvent {

public:
	ServerPacket Compose(SquareSession* session) override {
		Packets::Handshake::KeyExchangeRsp rsp{};

		auto packet = ServerPacket::Create <Opcode::KEY_EXCHANGE_RSP>();

		std::vector<char> key = session->GetConnection()->GetAuthenticateKeyPart();

		packet.WriteArray<char, 4>({
				key[0],
				key[1],
				key[2],
				key[3],
			});

		return packet;
	};
};

#endif