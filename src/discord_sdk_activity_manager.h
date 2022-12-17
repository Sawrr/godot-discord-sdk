#ifndef DISCORD_SDK_ACTIVITY_MANAGER_H
#define DISCORD_SDK_ACTIVITY_MANAGER_H

#include "discord_sdk_user.h"
#include "discord_sdk_activity.h"

#include "discord-sdk/core.h"
#include "discord_sdk.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

namespace sdk {

class DiscordActivityManager : public Object {
	GDCLASS(DiscordActivityManager, Object);

	static sdk::DiscordActivityManager *singleton;

protected:
	static void _bind_methods();

public:
	enum ActivityJoinRequestReply {
		No,
    	Yes,
    	Ignore
	};

	enum ActivityActionType {
	    Join = 1,
	    Spectate
	};
	
	static sdk::DiscordActivityManager *get_singleton();

	Discord::Result register_command(String command);
	void update_activity(Ref<sdk::DiscordActivity> activity, Callable callback);
	void clear_activity(Callable callback);
	void send_request_reply(int64_t user_id, ActivityJoinRequestReply reply, Callable callback);
	void send_invite(int64_t user_id, ActivityActionType type, String content, Callable callback);
	void accept_invite(int64_t user_id, Callable callback);

	void on_activity_join(Callable callback);
	void on_activity_spectate(Callable callback);
	void on_activity_join_request(Callable callback);
	void on_activity_invite(Callable callback);

	DiscordActivityManager();
	~DiscordActivityManager();
};

}

#endif // DISCORD_SDK_ACTIVITY_MANAGER_H
