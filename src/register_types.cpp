#include "register_types.h"

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "discord.h"
#include "discord_user.h"
#include "discord_user_manager.h"
#include "discord_relationship.h"
#include "discord_relationship_manager.h"
#include "discord_activity.h"
#include "discord_activity_manager.h"

using namespace godot;

static Discord * _discord;
static sdk::DiscordUserManager * _discordUserManager;
static sdk::DiscordRelationshipManager * _discordRelationshipManager;
static sdk::DiscordActivityManager * _discordActivityManager;

void initialize_discord_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<Discord>();
	ClassDB::register_class<sdk::DiscordUser>();
	ClassDB::register_class<sdk::DiscordUserManager>();
	ClassDB::register_class<sdk::DiscordRelationship>();
	ClassDB::register_class<sdk::DiscordRelationshipManager>();
	ClassDB::register_class<sdk::DiscordActivity>();
	ClassDB::register_class<sdk::DiscordActivityManager>();

	_discord = memnew(Discord);
	_discordUserManager = memnew(sdk::DiscordUserManager);
	_discordRelationshipManager = memnew(sdk::DiscordRelationshipManager);
	_discordActivityManager = memnew(sdk::DiscordActivityManager);
	Engine::get_singleton()->register_singleton("Discord", Discord::get_singleton());
	Engine::get_singleton()->register_singleton("DiscordUserManager", sdk::DiscordUserManager::get_singleton());
	Engine::get_singleton()->register_singleton("DiscordRelationshipManager", sdk::DiscordRelationshipManager::get_singleton());
	Engine::get_singleton()->register_singleton("DiscordActivityManager", sdk::DiscordActivityManager::get_singleton());
}

void uninitialize_discord_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization.
GDNativeBool GDN_EXPORT discord_library_init(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

	init_obj.register_initializer(initialize_discord_module);
	init_obj.register_terminator(uninitialize_discord_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
