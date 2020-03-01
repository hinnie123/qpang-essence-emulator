#include "game_net_event.hpp"
#include "game_connection.hpp"
#include "string_converter.hpp"

GameNetEvent::GameNetEvent()
	: NetEvent{ NetEvent::GuaranteedOrdered, NetEvent::DirUnset }
{

}

GameNetEvent::GameNetEvent(GameConnection* connection, GameNetId gameNetId, NetEvent::GuaranteeType guaranteeType, NetEvent::EventDirection eventDirection)
	: NetEvent{ guaranteeType, eventDirection },
	gameConnection{ connection },
	id{ gameNetId }

{

}

std::wstring GameNetEvent::GetString(ByteBuffer* byteBuffer)
{
	if (!byteBuffer->getBufferSize())
		return std::wstring();

	U8* buffer = byteBuffer->getBuffer();

	std::wstring wstring = std::wstring(reinterpret_cast<wchar_t*>(buffer), byteBuffer->getBufferSize() % 250);

	wstring = wstring.substr(0, wstring.size() % 255);

	return wstring;
}

void GameNetEvent::WriteBuffer(BitStream* stream, std::string data)
{
	std::wstring string = StringConverter::StringToWString(data);

	ByteBuffer b(reinterpret_cast<U8*>((char*)string.data()), string.size() * 2);
	stream->write(&b);
}

void GameNetEvent::WriteBuffer(BitStream * buffer, std::wstring data)
{
	return WriteBuffer(buffer, StringConverter::WStringToString(data));
}

std::wstring GameNetEvent::ReadBuffer(BitStream * stream)
{
	ByteBuffer* buffer = new ByteBuffer();

	stream->read(buffer);

	std::wstring string = GetString(buffer);

	buffer->clear();
	buffer->destroySelf();

	return string;
}

std::u16string GameNetEvent::ReadString(BitStream * buffer, uint32_t length)
{
	ByteBuffer* byteBuffer = new ByteBuffer(length);
	buffer->read(byteBuffer);

	uint32_t bufferStringLength = byteBuffer->getBufferSize() / 2 - 2;

	uint32_t sizeToCopy = (bufferStringLength > length ? length : bufferStringLength) * 2 + 2;

	std::u16string string;
	string.resize(sizeToCopy / 2 - 2);

	std::memcpy(string.data(), byteBuffer->getBuffer(), sizeToCopy);

	delete byteBuffer;

	return string;
}

void GameNetEvent::WriteString(BitStream * buffer, std::u16string string, uint32_t length)
{
	uint32_t sizeToCopy = (string.size() > length ? length : string.size()) * 2 + 2;

	ByteBuffer* byteBuffer = new ByteBuffer(sizeToCopy);

	std::memcpy(byteBuffer->getBuffer(), string.c_str(), sizeToCopy);

	buffer->write(byteBuffer);

	delete byteBuffer;
}

GameNetEvent::GameNetEvent(GameNetId gameNetId, NetEvent::GuaranteeType guaranteeType, NetEvent::EventDirection eventDirection)
	: NetEvent{ guaranteeType, eventDirection },
	id{ gameNetId }
{

}
