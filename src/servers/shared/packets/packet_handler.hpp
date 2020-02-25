#ifndef PACKET_HANDLER_HPP
#define PACKET_HANDLER_HPP

//std
#include <map>
#include "opcodes.hpp"
#include "packet_event.hpp"
#include "logger.hpp"

class PacketHandler {
public:
	//Base packet handler, normally gets overloaded.
	void Execute(Connection::Ptr conn, ClientPacket& pack)
	{
		if (_events.size() <= 0)
			return;

		if (!conn)
			return;

		if (conn->state != Connection::State::CONNECTED)
			return;

		auto header = pack.ReadPayloadHeader();
		Opcode code = header.opcode;

		auto set = _events.find(code);

		if (set != _events.cend())
		{
			auto theEvent = set->second;
			try
			{
				return theEvent->Read(conn, pack);
			}
			catch (std::exception & e)
			{
				sLogger->Get()->error("{0:d} -: {1}", code, e.what());
			}
		}
	};
protected:
	std::map<Opcode, PacketEvent*> _events;
};

#endif