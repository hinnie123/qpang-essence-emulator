#include "lobby_session.hpp"
#include "lobby_packet_handler.hpp"
#include "lobby.hpp"
#include "channel_manager.hpp"
#include "set_offline_event.hpp"

#include "trade.hpp"

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
	sLogger->Get()->info("Saving account details for: {0}", Info()->Nickname());
	//Use this function to save user info in the database. Gets called when user disconnects / server shutdown.
	Equipment()->Save(Info()->Id());
}

void LobbySession::Whisper(std::string message)
{
	Send(WhisperReceivedEvent{ "(!)", message }.Compose(nullptr));
}

void LobbySession::HandleClose()
{
	if (trades.count(userId))
	{
		// This person is still trading, cancel his trade before letting him go.
		trades[userId].tradingWith->Send(TradeCancelOtherEvent{ userId, 50 }.Compose(trades[userId].tradingWith));

		trades.erase(trades[userId].tradingWith->Info()->Id());
		trades.erase(userId);
	}

	_lobby->RemoveSession(userId);
}

LobbySession::~LobbySession()
{
	sLogger->Get()->debug("Destroy LobbySession {0:d}", Info()->Id());

	delete _infoManager;
	delete _equipmentManager;
	delete _inventoryManager;
	delete _messengerManager;
	delete _friendManager;
}