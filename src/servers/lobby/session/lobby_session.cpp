#include "lobby_session.hpp"
#include "lobby_packet_handler.hpp"
#include "lobby.hpp"
#include "channel_manager.hpp"
#include "set_offline_event.hpp"

LobbySession::LobbySession(Connection::Ptr connection)
	: Session{ connection }
{
	_connection->SetHandlers(
		std::bind(&LobbySession::HandlePacket, this, std::placeholders::_1),
		std::bind(&LobbySession::HandleClose, this));

	_infoManager = new InfoManager();
	_equipmentManager = new EquipmentManager();
	_inventoryManager = new InventoryManager();
	_messengerManager = new MessengerManager();
	_friendManager = new FriendManager();
}

void LobbySession::HandlePacket(ClientPacket& packet)
{
	if (_connection->state == Connection::State::CONNECTED)
		handler->Execute(this, packet);
}

void LobbySession::SetLobby(std::shared_ptr<Lobby> lobby)
{
	_lobby = lobby;
}

void LobbySession::Save()
{
	Equipment()->Save(Info()->Id());
}

void LobbySession::Whisper(std::u16string message)
{
	Send(WhisperReceivedEvent{ u"(!)", message }.Compose(nullptr));
}

void LobbySession::HandleClose()
{
	_lobby->RemoveSession(userId);
}

LobbySession::~LobbySession()
{
	delete _infoManager;
	delete _equipmentManager;
	delete _inventoryManager;
	delete _messengerManager;
	delete _friendManager;
}