#include "register_types.h"

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "discord_sdk.h"
#include "discord_sdk_user.h"
#include "discord_sdk_user_manager.h"
#include "discord_sdk_relationship.h"
#include "discord_sdk_relationship_manager.h"
#include "discord_sdk_activity.h"
#include "discord_sdk_activity_manager.h"
#include "discord_sdk_lobby.h"
#include "discord_sdk_lobby_transaction.h"

using namespace godot;

static DiscordSDK * _discord;
static DiscordSDKUserManager * _discordUserManager;
static DiscordSDKRelationshipManager * _discordRelationshipManager;
static DiscordSDKActivityManager * _discordActivityManager;

void initialize_discord_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<DiscordSDK>();
	ClassDB::register_class<DiscordSDKUser>();
	ClassDB::register_class<DiscordSDKUserManager>();
	ClassDB::register_class<DiscordSDKRelationship>();
	ClassDB::register_class<DiscordSDKRelationshipManager>();
	ClassDB::register_class<DiscordSDKActivity>();
	ClassDB::register_class<DiscordSDKActivityManager>();
	ClassDB::register_class<DiscordSDKLobby>();
	ClassDB::register_class<DiscordSDKLobbyTransaction>();


	_discord = memnew(DiscordSDK);
	_discordUserManager = memnew(DiscordSDKUserManager);
	_discordRelationshipManager = memnew(DiscordSDKRelationshipManager);
	_discordActivityManager = memnew(DiscordSDKActivityManager);
	Engine::get_singleton()->register_singleton("DiscordSDK", DiscordSDK::get_singleton());
	Engine::get_singleton()->register_singleton("DiscordSDKUserManager", DiscordSDKUserManager::get_singleton());
	Engine::get_singleton()->register_singleton("DiscordSDKRelationshipManager", DiscordSDKRelationshipManager::get_singleton());
	Engine::get_singleton()->register_singleton("DiscordSDKActivityManager", DiscordSDKActivityManager::get_singleton());
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
