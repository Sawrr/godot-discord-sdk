#ifndef DISCORD_SDK_ACTIVITY_H
#define DISCORD_SDK_ACTIVITY_H

#include "discord-sdk/types.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class DiscordSDKActivity : public RefCounted {
    GDCLASS(DiscordSDKActivity, RefCounted);

    discord::Activity activity{};

    protected:
        static void _bind_methods();
    
    public:
        int64_t get_application_id();
        String get_name();

        String get_state();
        void set_state(String state);
        String get_details();
        void set_details(String details);
        int64_t get_timestamp_start();
        void set_timestamp_start(int64_t time);
        int64_t get_timestamp_end();
        void set_timestamp_end(int64_t time);
        String get_large_image();
        void set_large_image(String image);
        String get_large_text();
        void set_large_text(String text);
        String get_small_image();
        void set_small_image(String image);
        String get_small_text();
        void set_small_text(String text);
        String get_party_id();
        void set_party_id(String id);
        int32_t get_party_current_size();
        void set_party_current_size(int32_t size);
        int32_t get_party_max_size();
        void set_party_max_size(int32_t size);
        String get_secret_match();
        void set_secret_match(String secret);
        String get_secret_join();
        void set_secret_join(String secret);
        String get_secret_spectate();
        void set_secret_spectate(String secret);
        bool get_instance();
        void set_instance(bool instance);

        DiscordSDKActivity() {}
        DiscordSDKActivity(discord::Activity act) {
            activity = act;
        }
};

#endif // DISCORD_SDK_ACTIVITY_H
