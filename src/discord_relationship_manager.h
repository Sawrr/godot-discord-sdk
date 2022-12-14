#ifndef DISCORD_SDK_RELATIONSHIP_MANAGER_H
#define DISCORD_SDK_RELATIONSHIP_MANAGER_H

#include "discord_relationship.h"

#include "discord-sdk/core.h"
#include "discord.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

namespace sdk {

class DiscordRelationshipManager : public Object {
	GDCLASS(DiscordRelationshipManager, Object);

	static sdk::DiscordRelationshipManager *singleton;

protected:
	static void _bind_methods();

public:
	static sdk::DiscordRelationshipManager *get_singleton();
	void filter(Callable condition);
	sdk::DiscordRelationship *get(int64_t user_id);
	sdk::DiscordRelationship *get_at(uint32_t index);
	int32_t count();
	
	void on_refresh(Callable callback);
	void on_relationship_update(Callable callback);

	DiscordRelationshipManager();
	~DiscordRelationshipManager();
};

}

#endif // DISCORD_SDK_RELATIONSHIP_MANAGER_H
