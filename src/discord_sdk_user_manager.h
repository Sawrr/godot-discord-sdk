#ifndef DISCORD_SDK_USER_MANAGER_H
#define DISCORD_SDK_USER_MANAGER_H

#include "discord_sdk_user.h"

#include "discord-sdk/core.h"
#include "discord_sdk.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


class DiscordSDKUserManager : public Object {
	GDCLASS(DiscordSDKUserManager, Object);

	static DiscordSDKUserManager *singleton;

protected:
	static void _bind_methods();

public:
	static DiscordSDKUserManager *get_singleton();
	DiscordSDKUser *get_current_user();
	void get_user(int64_t user_id, Callable callback);
	void on_current_user_update(Callable callback);

	DiscordSDKUserManager();
	~DiscordSDKUserManager();
};

#endif // DISCORD_SDK_USER_MANAGER_H
