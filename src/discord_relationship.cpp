
#include "discord_relationship.h"

VARIANT_ENUM_CAST(sdk::DiscordRelationship, RelationshipType);
VARIANT_ENUM_CAST(sdk::DiscordRelationship, Status);

void sdk::DiscordRelationship::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &sdk::DiscordRelationship::get_type);
	ClassDB::bind_method(D_METHOD("get_user"), &sdk::DiscordRelationship::get_user);
	ClassDB::bind_method(D_METHOD("get_status"), &sdk::DiscordRelationship::get_status);
    ClassDB::bind_method(D_METHOD("get_activity"), &sdk::DiscordRelationship::get_activity);

    BIND_ENUM_CONSTANT(None);
    BIND_ENUM_CONSTANT(Friend);
    BIND_ENUM_CONSTANT(Blocked);
    BIND_ENUM_CONSTANT(PendingIncoming);
    BIND_ENUM_CONSTANT(PendingOutgoing);
    BIND_ENUM_CONSTANT(Implicit);

    BIND_ENUM_CONSTANT(Offline);
    BIND_ENUM_CONSTANT(Online);
    BIND_ENUM_CONSTANT(Idle);
    BIND_ENUM_CONSTANT(DoNotDisturb);
}

sdk::DiscordRelationship::RelationshipType sdk::DiscordRelationship::get_type() {
    return static_cast<RelationshipType>(relationship.GetType());
}

sdk::DiscordUser *sdk::DiscordRelationship::get_user() {
    return memnew(sdk::DiscordUser(relationship.GetUser()));
}

sdk::DiscordRelationship::Status sdk::DiscordRelationship::get_status() {
    return static_cast<Status>(relationship.GetPresence().GetStatus());
}

sdk::DiscordActivity *sdk::DiscordRelationship::get_activity() {
    return memnew(sdk::DiscordActivity(relationship.GetPresence().GetActivity()));
}
