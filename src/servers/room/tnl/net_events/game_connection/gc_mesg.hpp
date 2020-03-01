#ifndef GC_MESG_HPP
#define GC_MESG_HPP

#include "game_net_event.hpp"
#include <string>
#include "string_converter.hpp"

class GCMesg : public GameNetEvent
{
	typedef NetEvent Parent;
public:
	GCMesg() : GameNetEvent{ GC_MESG, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirAny } {};
	GCMesg(const U32& playerId, const U32& cmd, std::u16string nickname, std::u16string message) : GameNetEvent{ GC_MESG, NetEvent::GuaranteeType::Unguaranteed, NetEvent::DirAny } 
	{	
		this->playerId = playerId;
		this->cmd = cmd; // 8 = message without sender?
		this->nickname = nickname;
		this->message = message;
	};
	void pack(EventConnection* conn, BitStream* bstream) 
	{
		bstream->write(playerId);
		bstream->write(cmd);
		WriteString(bstream, nickname, 16);
		WriteString(bstream, message, message.size() % 254);
	};
	void unpack(EventConnection* conn, BitStream* bstream) {};
	void process(EventConnection* ps) {};

	U32 playerId;
	U32 cmd;

	std::u16string nickname;
	std::u16string message;

	TNL_DECLARE_CLASS(GCMesg);
};

#endif // !GC_ARRANGED_ACCEPT_HPP