
#include "discord_sdk_relationship.h"

void DiscordSDKRelationship::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_type"), &DiscordSDKRelationship::get_type);
	ClassDB::bind_method(D_METHOD("get_user"), &DiscordSDKRelationship::get_user);
	ClassDB::bind_method(D_METHOD("get_status"), &DiscordSDKRelationship::get_status);

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

DiscordSDKRelationship::RelationshipType DiscordSDKRelationship::get_type() {
    return static_cast<RelationshipType>(relationship.GetType());
}

DiscordSDKUser *DiscordSDKRelationship::get_user() {
    return memnew(DiscordSDKUser(relationship.GetUser()));
}

DiscordSDKRelationship::Status DiscordSDKRelationship::get_status() {
    return static_cast<Status>(relationship.GetPresence().GetStatus());
}
