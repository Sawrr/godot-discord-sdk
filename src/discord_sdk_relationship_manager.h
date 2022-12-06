#ifndef DISCORD_SDK_RELATIONSHIP_MANAGER_H
#define DISCORD_SDK_RELATIONSHIP_MANAGER_H

#include "discord_sdk_relationship.h"

#include "discord-sdk/core.h"
#include "discord_sdk.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


class DiscordSDKRelationshipManager : public Object {
	GDCLASS(DiscordSDKRelationshipManager, Object);

	static DiscordSDKRelationshipManager *singleton;

protected:
	static void _bind_methods();

public:
	static DiscordSDKRelationshipManager *get_singleton();
	void filter(Callable condition);
	DiscordSDKRelationship *get(int64_t user_id);
	DiscordSDKRelationship *get_at(uint32_t index);
	int32_t count();
	
	void on_refresh(Callable callback);
	void on_relationship_update(Callable callback);

	DiscordSDKRelationshipManager();
	~DiscordSDKRelationshipManager();
};

#endif // DISCORD_SDK_RELATIONSHIP_MANAGER_H
