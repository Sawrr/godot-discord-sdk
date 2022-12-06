#include "discord_sdk_user_manager.h"

using namespace godot;

DiscordSDKUserManager *DiscordSDKUserManager::singleton = nullptr;

DiscordSDKUserManager * DiscordSDKUserManager::get_singleton() {
    return singleton;
}

DiscordSDKUserManager::DiscordSDKUserManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordSDKUserManager::~DiscordSDKUserManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void DiscordSDKUserManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_current_user"), &DiscordSDKUserManager::get_current_user);
	ClassDB::bind_method(D_METHOD("get_user", "user_id"), &DiscordSDKUserManager::get_user);
	ClassDB::bind_method(D_METHOD("on_current_user_update"), &DiscordSDKUserManager::on_current_user_update);
}

DiscordSDKUser *DiscordSDKUserManager::get_current_user() {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);
	
	discord::User currentUser{};
	discord::Result result = DiscordSDK::get_singleton()->core->UserManager().GetCurrentUser(&currentUser);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, nullptr, "Failed to retrieve current Discord user.");

	return memnew(DiscordSDKUser(currentUser));
}

void DiscordSDKUserManager::get_user(int64_t user_id, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);
	
	DiscordSDK::get_singleton()->core->UserManager().GetUser(user_id, [=](discord::Result result, const discord::User &user) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to retrieve Discord user.");
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		args.append(memnew(DiscordSDKUser(user)));
		callback.callv(args);
	});
}

void DiscordSDKUserManager::on_current_user_update(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->UserManager().OnCurrentUserUpdate.Connect(
		[=]() {
			Array args{};
			callback.callv(args);
		}
	);
}
