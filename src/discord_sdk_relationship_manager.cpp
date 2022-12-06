#include "discord_sdk_relationship_manager.h"

using namespace godot;

DiscordSDKRelationshipManager *DiscordSDKRelationshipManager::singleton = nullptr;

DiscordSDKRelationshipManager * DiscordSDKRelationshipManager::get_singleton() {
    return singleton;
}

DiscordSDKRelationshipManager::DiscordSDKRelationshipManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordSDKRelationshipManager::~DiscordSDKRelationshipManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void DiscordSDKRelationshipManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("filter", "condition"), &DiscordSDKRelationshipManager::filter);
	ClassDB::bind_method(D_METHOD("get", "user_id"), &DiscordSDKRelationshipManager::get);
	ClassDB::bind_method(D_METHOD("get_at", "index"), &DiscordSDKRelationshipManager::get_at);
	ClassDB::bind_method(D_METHOD("count"), &DiscordSDKRelationshipManager::count);
	ClassDB::bind_method(D_METHOD("on_refresh", "callback"), &DiscordSDKRelationshipManager::on_refresh);
	ClassDB::bind_method(D_METHOD("on_relationship_update", "callback"), &DiscordSDKRelationshipManager::on_relationship_update);
}

void DiscordSDKRelationshipManager::filter(Callable condition) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);
	DiscordSDK::get_singleton()->core->RelationshipManager().Filter([=](const discord::Relationship &relationship) {
		Array args;
		args.append(memnew(DiscordSDKRelationship(relationship)));
		return condition.callv(args);
	});
}

DiscordSDKRelationship *DiscordSDKRelationshipManager::get(int64_t user_id) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);
	
	discord::Relationship relationship{};
	discord::Result result = DiscordSDK::get_singleton()->core->RelationshipManager().Get(user_id, &relationship);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, nullptr, "Failed to retrieve Discord relationship of user_id.");

	return memnew(DiscordSDKRelationship(relationship));
}

DiscordSDKRelationship *DiscordSDKRelationshipManager::get_at(uint32_t index) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);
	
	discord::Relationship relationship{};
	discord::Result result = DiscordSDK::get_singleton()->core->RelationshipManager().GetAt(index, &relationship);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, nullptr, "Failed to retrieve Discord relationship at index.");

	return memnew(DiscordSDKRelationship(relationship));
}

int32_t DiscordSDKRelationshipManager::count() {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, -1, DISCORD_SDK_ERR_NOT_INIT);

	int32_t count;
	discord::Result result =  DiscordSDK::get_singleton()->core->RelationshipManager().Count(&count);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, -1, "Failed to retrieve Discord relationship count.");

	return count;
}

void DiscordSDKRelationshipManager::on_refresh(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->RelationshipManager().OnRefresh.Connect(
		[=]() {
			Array args{};
			callback.callv(args);
		}
	);
}

void DiscordSDKRelationshipManager::on_relationship_update(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->RelationshipManager().OnRelationshipUpdate.Connect(
		[=](discord::Relationship relationship) {
			Array args{};
			args.append(memnew(DiscordSDKRelationship(relationship)));
			callback.callv(args);
		}
	);
}
