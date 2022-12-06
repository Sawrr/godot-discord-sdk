#include "discord_sdk_activity_manager.h"

using namespace godot;

DiscordSDKActivityManager *DiscordSDKActivityManager::singleton = nullptr;

DiscordSDKActivityManager * DiscordSDKActivityManager::get_singleton() {
    return singleton;
}

DiscordSDKActivityManager::DiscordSDKActivityManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordSDKActivityManager::~DiscordSDKActivityManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void DiscordSDKActivityManager::_bind_methods() {
	BIND_ENUM_CONSTANT(No);
    BIND_ENUM_CONSTANT(Yes);
    BIND_ENUM_CONSTANT(Ignore);

    BIND_ENUM_CONSTANT(Join);
	BIND_ENUM_CONSTANT(Spectate);
	
	ClassDB::bind_method(D_METHOD("register_command", "command"), &DiscordSDKActivityManager::register_command);
	ClassDB::bind_method(D_METHOD("update_activity", "activity", "callback"), &DiscordSDKActivityManager::update_activity);
	ClassDB::bind_method(D_METHOD("clear_activity", "callback"), &DiscordSDKActivityManager::clear_activity);
	ClassDB::bind_method(D_METHOD("send_request_reply", "user_id", "reply", "callback"), &DiscordSDKActivityManager::send_request_reply);
	ClassDB::bind_method(D_METHOD("send_invite", "user_id", "type", "content", "callback"), &DiscordSDKActivityManager::send_invite);
	ClassDB::bind_method(D_METHOD("accept_invite", "user_id", "callback"), &DiscordSDKActivityManager::accept_invite);

	ClassDB::bind_method(D_METHOD("on_activity_join", "callback"), &DiscordSDKActivityManager::on_activity_join);
	ClassDB::bind_method(D_METHOD("on_activity_spectate", "callback"), &DiscordSDKActivityManager::on_activity_spectate);
	ClassDB::bind_method(D_METHOD("on_activity_join_request", "callback"), &DiscordSDKActivityManager::on_activity_join_request);
	ClassDB::bind_method(D_METHOD("on_activity_invite", "callback"), &DiscordSDKActivityManager::on_activity_invite);
}

DiscordSDK::Result DiscordSDKActivityManager::register_command(String command) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, static_cast<DiscordSDK::Result>(-1), DISCORD_SDK_ERR_NOT_INIT);

	return static_cast<DiscordSDK::Result>(DiscordSDK::get_singleton()->core->ActivityManager().RegisterCommand(command.utf8().get_data()));
}

void DiscordSDKActivityManager::update_activity(Ref<DiscordSDKActivity> activity, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().UpdateActivity(activity->activity, [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to update Discord activity.");
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKActivityManager::clear_activity(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().ClearActivity([=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to clear Discord activity.");
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKActivityManager::send_request_reply(int64_t user_id, ActivityJoinRequestReply reply, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().SendRequestReply(user_id, static_cast<discord::ActivityJoinRequestReply>(reply), [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to send Discord request reply.");
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKActivityManager::send_invite(int64_t user_id, ActivityActionType type, String content, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().SendInvite(user_id, static_cast<discord::ActivityActionType>(type), content.utf8().get_data(), [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to send Discord invite.");
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKActivityManager::accept_invite(int64_t user_id, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().AcceptInvite(user_id, [=](discord::Result result) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to accept Discord invite.");
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKActivityManager::on_activity_join(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().OnActivityJoin.Connect(
		[=](const char * joinSecret) {
			Array args{};
			args.append(String(joinSecret));
			callback.callv(args);
		}
	);
}

void DiscordSDKActivityManager::on_activity_spectate(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().OnActivitySpectate.Connect(
		[=](const char * spectateSecret) {
			Array args{};
			args.append(String(spectateSecret));
			callback.callv(args);
		}
	);
}

void DiscordSDKActivityManager::on_activity_join_request(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().OnActivityJoinRequest.Connect(
		[=](const discord::User &user) {
			Array args{};
			args.append(memnew(DiscordSDKUser(user)));
			callback.callv(args);
		}
	);
}

void DiscordSDKActivityManager::on_activity_invite(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->ActivityManager().OnActivityInvite.Connect(
		[=](discord::ActivityActionType type, const discord::User &user, const discord::Activity &activity) {
			Array args{};
			args.append(static_cast<ActivityActionType>(type));
			args.append(memnew(DiscordSDKUser(user)));
			args.append(memnew(DiscordSDKActivity(activity)));
			callback.callv(args);
		}
	);
}
