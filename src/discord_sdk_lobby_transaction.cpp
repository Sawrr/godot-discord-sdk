
#include "discord_sdk_lobby_transaction.h"

void DiscordSDKLobbyTransaction::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_lobby_type", "type"), &DiscordSDKLobbyTransaction::set_lobby_type);
    ClassDB::bind_method(D_METHOD("set_owner_id", "id"), &DiscordSDKLobbyTransaction::set_owner_id);
    ClassDB::bind_method(D_METHOD("set_capacity", "capacity"), &DiscordSDKLobbyTransaction::set_capacity);
    ClassDB::bind_method(D_METHOD("set_locked", "locked"), &DiscordSDKLobbyTransaction::set_locked);
}

void DiscordSDKLobbyTransaction::set_lobby_type(DiscordSDKLobby::LobbyType type) {
    lobbyTransaction.SetType(static_cast<discord::LobbyType>(type));
}

void DiscordSDKLobbyTransaction::set_owner_id(int64_t id) {
    lobbyTransaction.SetOwner(id);
}

void DiscordSDKLobbyTransaction::set_capacity(uint32_t capacity) {
    lobbyTransaction.SetCapacity(capacity);
}

void DiscordSDKLobbyTransaction::set_locked(bool locked) {
    lobbyTransaction.SetLocked(locked);
}
