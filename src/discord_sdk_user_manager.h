#ifndef DISCORD_SDK_USER_MANAGER_H
#define DISCORD_SDK_USER_MANAGER_H

#include "discord_sdk_user.h"

#include "discord-sdk/core.h"
#include "discord_sdk.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

namespace sdk {

class DiscordUserManager : public Object {
	GDCLASS(DiscordUserManager, Object);

	static sdk::DiscordUserManager *singleton;

protected:
	static void _bind_methods();

public:
	static sdk::DiscordUserManager *get_singleton();
	sdk::DiscordUser *get_current_user();
	void get_user(int64_t user_id, Callable callback);
	void on_current_user_update(Callable callback);

	DiscordUserManager();
	~DiscordUserManager();
};

}

#endif // DISCORD_SDK_USER_MANAGER_H
