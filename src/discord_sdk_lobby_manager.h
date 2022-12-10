#ifndef DISCORD_SDK_LOBBY_MANAGER_H
#define DISCORD_SDK_LOBBY_MANAGER_H

#include "discord_sdk_user.h"
#include "discord_sdk_lobby.h"
#include "discord_sdk_lobby_transaction.h"

#include "discord-sdk/core.h"
#include "discord_sdk.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;


class DiscordSDKLobbyManager : public Object {
	GDCLASS(DiscordSDKLobbyManager, Object);

	static DiscordSDKLobbyManager *singleton;

protected:
	static void _bind_methods();

public:	
	static DiscordSDKLobbyManager *get_singleton();

	DiscordSDKLobbyTransaction * get_lobby_create_transaction();
	DiscordSDKLobbyTransaction * get_lobby_update_transaction(int64_t lobby_id);
	void create_lobby(Ref<DiscordSDKLobbyTransaction> transaction, Callable callback);
	void update_lobby(int64_t lobby_id, Ref<DiscordSDKLobbyTransaction> transaction, Callable callback);
	void delete_lobby(int64_t lobby_id, Callable callback);
	void connect_lobby_with_activity_secret(String activity_secret, Callable callback);
	String get_lobby_activity_secret(int64_t lobby_id);
	void disconnect_lobby(int64_t lobby_id, Callable callback);
	int32_t member_count(int64_t lobby_id);
	int64_t get_member_user_id(int64_t lobby_id, int32_t index);
	DiscordSDKUser * get_member_user(int64_t lobby_id, int64_t user_id);

	void on_lobby_update(Callable callback);
	void on_lobby_delete(Callable callback);
	void on_member_connect(Callable callback);
	void on_member_update(Callable callback);
	void on_member_disconnect(Callable callback);

	void connect_network(int64_t lobby_id);
	void disconnect_network(int64_t lobby_id);
	void flush_network();

	void open_network_channel(int64_t lobby_id, int8_t channel_id, bool reliable);
	void send_network_message(int64_t lobby_id, int64_t user_id, int8_t channel_id, Dictionary data);

	void on_network_message(Callable callback);

	DiscordSDKLobbyManager();
	~DiscordSDKLobbyManager();
};

#endif // DISCORD_SDK_LOBBY_MANAGER_H
