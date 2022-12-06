#ifndef DISCORD_SDK_USER_H
#define DISCORD_SDK_USER_H

#include "discord-sdk/types.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class DiscordSDKUser : public RefCounted {
    GDCLASS(DiscordSDKUser, RefCounted);

    discord::User user{};

    protected:
        static void _bind_methods();
    
    public:
        void set_id(int64_t id);
        int64_t get_id();
        void set_username(String username);
        String get_username();
        void set_discriminator(String discriminator);
        String get_discriminator();
        void set_avatar(String avatar);
        String get_avatar();
        void set_bot(bool bot);
        bool get_bot();

        DiscordSDKUser() {}
        DiscordSDKUser(discord::User usr) {
            user = usr;
        }
};

#endif // DISCORD_SDK_USER_H