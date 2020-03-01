#ifndef HANDSHAKE_EVENT_HPP
#define HANDSHAKE_EVENT_HPP

#include "square_packet_event.hpp"
#include "handshake_response_event.hpp"

class HandshakeEvent : public SquarePacketEvent {
		
public:
	HandshakeEvent() : SquarePacketEvent(sizeof(Packets::Handshake::KeyExchange)) {};
	void Read(SquareSession* session, ClientPacket& pack) override
	{
		session->Send(HandshakeResponseEvent{}.Compose(session), BlowfishContext::CryptoType::PUBLIC);
	}
};

#endif