#include "discord_activity_manager.h"

using namespace godot;

VARIANT_ENUM_CAST(sdk::DiscordActivityManager, ActivityJoinRequestReply);
VARIANT_ENUM_CAST(sdk::DiscordActivityManager, ActivityActionType);

sdk::DiscordActivityManager *sdk::DiscordActivityManager::singleton = nullptr;

sdk::DiscordActivityManager * sdk::DiscordActivityManager::get_singleton() {
    return singleton;
}

sdk::DiscordActivityManager::DiscordActivityManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

sdk::DiscordActivityManager::~DiscordActivityManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void sdk::DiscordActivityManager::_bind_methods() {
	BIND_ENUM_CONSTANT(No);
    BIND_ENUM_CONSTANT(Yes);
    BIND_ENUM_CONSTANT(Ignore);

    BIND_ENUM_CONSTANT(Join);
	BIND_ENUM_CONSTANT(Spectate);
	
	ClassDB::bind_method(D_METHOD("register_command", "command"), &sdk::DiscordActivityManager::register_command);
	ClassDB::bind_method(D_METHOD("register_steam", "steam_id"), &sdk::DiscordActivityManager::register_steam);
	ClassDB::bind_method(D_METHOD("update_activity", "activity", "callback"), &sdk::DiscordActivityManager::update_activity);
	ClassDB::bind_method(D_METHOD("clear_activity", "callback"), &sdk::DiscordActivityManager::clear_activity);
	ClassDB::bind_method(D_METHOD("send_request_reply", "user_id", "reply", "callback"), &sdk::DiscordActivityManager::send_request_reply);
	ClassDB::bind_method(D_METHOD("send_invite", "user_id", "type", "content", "callback"), &sdk::DiscordActivityManager::send_invite);
	ClassDB::bind_method(D_METHOD("accept_invite", "user_id", "callback"), &sdk::DiscordActivityManager::accept_invite);

	ClassDB::bind_method(D_METHOD("on_activity_join", "callback"), &sdk::DiscordActivityManager::on_activity_join);
	ClassDB::bind_method(D_METHOD("on_activity_spectate", "callback"), &sdk::DiscordActivityManager::on_activity_spectate);
	ClassDB::bind_method(D_METHOD("on_activity_join_request", "callback"), &sdk::DiscordActivityManager::on_activity_join_request);
	ClassDB::bind_method(D_METHOD("on_activity_invite", "callback"), &sdk::DiscordActivityManager::on_activity_invite);
}

Discord::Result sdk::DiscordActivityManager::register_command(String command) {
	ERR_FAIL_COND_V_MSG(!Discord::get_singleton()->core, static_cast<Discord::Result>(-1), DISCORD_SDK_ERR_NOT_INIT);

	return static_cast<Discord::Result>(Discord::get_singleton()->core->ActivityManager().RegisterCommand(command.utf8().get_data()));
}

Discord::Result sdk::DiscordActivityManager::register_steam(uint32_t steam_id) {
	ERR_FAIL_COND_V_MSG(!Discord::get_singleton()->core, static_cast<Discord::Result>(-1), DISCORD_SDK_ERR_NOT_INIT);

	return static_cast<Discord::Result>(Discord::get_singleton()->core->ActivityManager().RegisterSteam(steam_id));
}

void sdk::DiscordActivityManager::update_activity(Ref<sdk::DiscordActivity> activity, Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().UpdateActivity(activity->activity, [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to update Discord activity.");
		Array args{};
		args.append(static_cast<Discord::Result>(result));
		callback.callv(args);
	});
}

void sdk::DiscordActivityManager::clear_activity(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().ClearActivity([=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to clear Discord activity.");
		Array args{};
		args.append(static_cast<Discord::Result>(result));
		callback.callv(args);
	});
}

void sdk::DiscordActivityManager::send_request_reply(int64_t user_id, ActivityJoinRequestReply reply, Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().SendRequestReply(user_id, static_cast<discord::ActivityJoinRequestReply>(reply), [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to send Discord request reply.");
		Array args{};
		args.append(static_cast<Discord::Result>(result));
		callback.callv(args);
	});
}

void sdk::DiscordActivityManager::send_invite(int64_t user_id, ActivityActionType type, String content, Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().SendInvite(user_id, static_cast<discord::ActivityActionType>(type), content.utf8().get_data(), [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to send Discord invite.");
		Array args{};
		args.append(static_cast<Discord::Result>(result));
		callback.callv(args);
	});
}

void sdk::DiscordActivityManager::accept_invite(int64_t user_id, Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().AcceptInvite(user_id, [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to accept Discord invite.");
		Array args{};
		args.append(static_cast<Discord::Result>(result));
		callback.callv(args);
	});
}

void sdk::DiscordActivityManager::on_activity_join(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().OnActivityJoin.Connect(
		[=](const char * joinSecret) {
			Array args{};
			args.append(String(joinSecret));
			callback.callv(args);
		}
	);
}

void sdk::DiscordActivityManager::on_activity_spectate(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().OnActivitySpectate.Connect(
		[=](const char * spectateSecret) {
			Array args{};
			args.append(String(spectateSecret));
			callback.callv(args);
		}
	);
}

void sdk::DiscordActivityManager::on_activity_join_request(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().OnActivityJoinRequest.Connect(
		[=](const discord::User &user) {
			Array args{};
			args.append(memnew(sdk::DiscordUser(user)));
			callback.callv(args);
		}
	);
}

void sdk::DiscordActivityManager::on_activity_invite(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->ActivityManager().OnActivityInvite.Connect(
		[=](discord::ActivityActionType type, const discord::User &user, const discord::Activity &activity) {
			Array args{};
			args.append(static_cast<ActivityActionType>(type));
			args.append(memnew(sdk::DiscordUser(user)));
			args.append(memnew(sdk::DiscordActivity(activity)));
			callback.callv(args);
		}
	);
}
