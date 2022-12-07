#ifndef DISCORD_SDK_LOBBY_H
#define DISCORD_SDK_LOBBY_H

#include "discord-sdk/types.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class DiscordSDKLobby : public RefCounted {
    GDCLASS(DiscordSDKLobby, RefCounted);

    discord::Lobby lobby{};

    protected:
        static void _bind_methods();
    
    public:
        enum LobbyType {
            Private = 1,
            Public,
        };

        int64_t get_id();
        LobbyType get_lobby_type();
        int64_t get_owner_id();
        String get_secret();
        uint32_t get_capacity();
        bool get_locked();

        DiscordSDKLobby() {}
        DiscordSDKLobby(discord::Lobby lob) {
            lobby = lob;
        }
};

VARIANT_ENUM_CAST(DiscordSDKLobby, LobbyType);

#endif // DISCORD_SDK_LOBBY_H