#ifndef DISCORD_SDK_LOBBY_TRANSACTION_H
#define DISCORD_SDK_LOBBY_TRANSACTION_H

#include "discord_sdk_lobby.h"

#include "discord-sdk/types.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class DiscordSDKLobbyTransaction : public RefCounted {
    GDCLASS(DiscordSDKLobbyTransaction, RefCounted);

    discord::LobbyTransaction lobbyTransaction{};

    protected:
        static void _bind_methods();
    
    public:
        void set_lobby_type(DiscordSDKLobby::LobbyType type);
        void set_owner_id(int64_t id);
        void set_capacity(uint32_t capacity);
        void set_locked(bool locked);

        DiscordSDKLobbyTransaction() {}
        DiscordSDKLobbyTransaction(discord::LobbyTransaction lob) {
            lobbyTransaction = lob;
        }
};

#endif // DISCORD_SDK_LOBBY_TRANSACTION_H