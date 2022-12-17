#include "discord_sdk_relationship_manager.h"

using namespace godot;

sdk::DiscordRelationshipManager *sdk::DiscordRelationshipManager::singleton = nullptr;

sdk::DiscordRelationshipManager * sdk::DiscordRelationshipManager::get_singleton() {
    return singleton;
}

sdk::DiscordRelationshipManager::DiscordRelationshipManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

sdk::DiscordRelationshipManager::~DiscordRelationshipManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void sdk::DiscordRelationshipManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("filter", "condition"), &sdk::DiscordRelationshipManager::filter);
	ClassDB::bind_method(D_METHOD("get", "user_id"), &sdk::DiscordRelationshipManager::get);
	ClassDB::bind_method(D_METHOD("get_at", "index"), &sdk::DiscordRelationshipManager::get_at);
	ClassDB::bind_method(D_METHOD("count"), &sdk::DiscordRelationshipManager::count);
	ClassDB::bind_method(D_METHOD("on_refresh", "callback"), &sdk::DiscordRelationshipManager::on_refresh);
	ClassDB::bind_method(D_METHOD("on_relationship_update", "callback"), &sdk::DiscordRelationshipManager::on_relationship_update);
}

void sdk::DiscordRelationshipManager::filter(Callable condition) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->RelationshipManager().Filter([=](const discord::Relationship &relationship) {
		Array args;
		args.append(memnew(sdk::DiscordRelationship(relationship)));
		return condition.callv(args);
	});
}

sdk::DiscordRelationship *sdk::DiscordRelationshipManager::get(int64_t user_id) {
	ERR_FAIL_COND_V_MSG(!Discord::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);
	
	discord::Relationship relationship{};
	discord::Result result = Discord::get_singleton()->core->RelationshipManager().Get(user_id, &relationship);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, nullptr, "Failed to retrieve Discord relationship of user_id.");

	return memnew(sdk::DiscordRelationship(relationship));
}

sdk::DiscordRelationship *sdk::DiscordRelationshipManager::get_at(uint32_t index) {
	ERR_FAIL_COND_V_MSG(!Discord::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);
	
	discord::Relationship relationship{};
	discord::Result result = Discord::get_singleton()->core->RelationshipManager().GetAt(index, &relationship);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, nullptr, "Failed to retrieve Discord relationship at index.");

	return memnew(sdk::DiscordRelationship(relationship));
}

int32_t sdk::DiscordRelationshipManager::count() {
	ERR_FAIL_COND_V_MSG(!Discord::get_singleton()->core, -1, DISCORD_SDK_ERR_NOT_INIT);

	int32_t count;
	discord::Result result =  Discord::get_singleton()->core->RelationshipManager().Count(&count);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, -1, "Failed to retrieve Discord relationship count.");

	return count;
}

void sdk::DiscordRelationshipManager::on_refresh(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->RelationshipManager().OnRefresh.Connect(
		[=]() {
			Array args{};
			callback.callv(args);
		}
	);
}

void sdk::DiscordRelationshipManager::on_relationship_update(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->RelationshipManager().OnRelationshipUpdate.Connect(
		[=](discord::Relationship relationship) {
			Array args{};
			args.append(memnew(sdk::DiscordRelationship(relationship)));
			callback.callv(args);
		}
	);
}
