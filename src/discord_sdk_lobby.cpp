
#include "discord_sdk_lobby.h"

void DiscordSDKLobby::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_id"), &DiscordSDKLobby::get_id);
    ClassDB::bind_method(D_METHOD("get_lobby_type"), &DiscordSDKLobby::get_lobby_type);
    ClassDB::bind_method(D_METHOD("get_owner_id"), &DiscordSDKLobby::get_owner_id);
    ClassDB::bind_method(D_METHOD("get_secret"), &DiscordSDKLobby::get_secret);
    ClassDB::bind_method(D_METHOD("get_capacity"), &DiscordSDKLobby::get_capacity);
    ClassDB::bind_method(D_METHOD("get_locked"), &DiscordSDKLobby::get_locked);

    BIND_ENUM_CONSTANT(Private);
    BIND_ENUM_CONSTANT(Public);
}

int64_t DiscordSDKLobby::get_id() {
    return lobby.GetId();
}

DiscordSDKLobby::LobbyType DiscordSDKLobby::get_lobby_type() {
    return static_cast<LobbyType>(lobby.GetType());
}

int64_t DiscordSDKLobby::get_owner_id() {
    return lobby.GetOwnerId();
}

String DiscordSDKLobby::get_secret() {
    return lobby.GetSecret();
}

uint32_t DiscordSDKLobby::get_capacity() {
    return lobby.GetCapacity();
}

bool DiscordSDKLobby::get_locked() {
    return lobby.GetLocked();
}
