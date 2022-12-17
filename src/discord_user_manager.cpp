#include "discord_user_manager.h"

using namespace godot;

sdk::DiscordUserManager *sdk::DiscordUserManager::singleton = nullptr;

sdk::DiscordUserManager * sdk::DiscordUserManager::get_singleton() {
    return singleton;
}

sdk::DiscordUserManager::DiscordUserManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

sdk::DiscordUserManager::~DiscordUserManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void sdk::DiscordUserManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_current_user"), &sdk::DiscordUserManager::get_current_user);
	ClassDB::bind_method(D_METHOD("get_user", "user_id"), &sdk::DiscordUserManager::get_user);
	ClassDB::bind_method(D_METHOD("on_current_user_update"), &sdk::DiscordUserManager::on_current_user_update);
}

sdk::DiscordUser *sdk::DiscordUserManager::get_current_user() {
	ERR_FAIL_COND_V_MSG(!Discord::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);
	
	discord::User currentUser{};
	discord::Result result = Discord::get_singleton()->core->UserManager().GetCurrentUser(&currentUser);
	ERR_FAIL_COND_V_MSG(result != discord::Result::Ok, nullptr, "Failed to retrieve current Discord user.");

	return memnew(sdk::DiscordUser(currentUser));
}

void sdk::DiscordUserManager::get_user(int64_t user_id, Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);
	
	Discord::get_singleton()->core->UserManager().GetUser(user_id, [=](discord::Result result, const discord::User &user) {
		ERR_FAIL_COND_MSG(result != discord::Result::Ok, "Failed to retrieve Discord user.");
		Array args{};
		args.append(static_cast<Discord::Result>(result));
		args.append(memnew(sdk::DiscordUser(user)));
		callback.callv(args);
	});
}

void sdk::DiscordUserManager::on_current_user_update(Callable callback) {
	ERR_FAIL_COND_MSG(!Discord::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	Discord::get_singleton()->core->UserManager().OnCurrentUserUpdate.Connect(
		[=]() {
			Array args{};
			callback.callv(args);
		}
	);
}
