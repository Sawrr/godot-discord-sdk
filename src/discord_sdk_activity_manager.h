#ifndef DISCORD_SDK_ACTIVITY_MANAGER_H
#define DISCORD_SDK_ACTIVITY_MANAGER_H

#include "discord_sdk_user.h"
#include "discord_sdk_activity.h"

#include "discord-sdk/core.h"
#include "discord_sdk.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


class DiscordSDKActivityManager : public Object {
	GDCLASS(DiscordSDKActivityManager, Object);

	static DiscordSDKActivityManager *singleton;

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
	
	static DiscordSDKActivityManager *get_singleton();

	DiscordSDK::Result register_command(String command);
	void update_activity(Ref<DiscordSDKActivity> activity, Callable callback);
	void clear_activity(Callable callback);
	void send_request_reply(int64_t user_id, ActivityJoinRequestReply reply, Callable callback);
	void send_invite(int64_t user_id, ActivityActionType type, String content, Callable callback);
	void accept_invite(int64_t user_id, Callable callback);

	void on_activity_join(Callable callback);
	void on_activity_spectate(Callable callback);
	void on_activity_join_request(Callable callback);
	void on_activity_invite(Callable callback);

	DiscordSDKActivityManager();
	~DiscordSDKActivityManager();
};

VARIANT_ENUM_CAST(DiscordSDKActivityManager, ActivityJoinRequestReply);
VARIANT_ENUM_CAST(DiscordSDKActivityManager, ActivityActionType);

#endif // DISCORD_SDK_ACTIVITY_MANAGER_H
