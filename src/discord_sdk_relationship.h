#ifndef DISCORD_SDK_RELATIONSHIP_H
#define DISCORD_SDK_RELATIONSHIP_H

#include "discord_sdk_user.h"

#include "discord-sdk/types.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class DiscordSDKRelationship : public RefCounted {
    GDCLASS(DiscordSDKRelationship, RefCounted);

    discord::Relationship relationship{};

    protected:
        static void _bind_methods();
    
    public:
        enum RelationshipType {
            None,
            Friend,
            Blocked,
            PendingIncoming,
            PendingOutgoing,
            Implicit,
        };

        enum Status {
            Offline = 0,
            Online = 1,
            Idle = 2,
            DoNotDisturb = 3,
        };

        RelationshipType get_type();
        DiscordSDKUser *get_user();
        Status get_status();

        DiscordSDKRelationship() {}
        DiscordSDKRelationship(discord::Relationship rel) {
            relationship = rel;
        }
};

VARIANT_ENUM_CAST(DiscordSDKRelationship, RelationshipType);
VARIANT_ENUM_CAST(DiscordSDKRelationship, Status);

#endif // DISCORD_SDK_RELATIONSHIP_H