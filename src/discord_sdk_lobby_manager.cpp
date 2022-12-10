#include "discord_sdk_lobby_manager.h"

using namespace godot;

DiscordSDKLobbyManager *DiscordSDKLobbyManager::singleton = nullptr;

DiscordSDKLobbyManager * DiscordSDKLobbyManager::get_singleton() {
    return singleton;
}

DiscordSDKLobbyManager::DiscordSDKLobbyManager() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

DiscordSDKLobbyManager::~DiscordSDKLobbyManager() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void DiscordSDKLobbyManager::_bind_methods() {	
	ClassDB::bind_method(D_METHOD("get_lobby_create_transaction"), &DiscordSDKLobbyManager::get_lobby_create_transaction);
	ClassDB::bind_method(D_METHOD("get_lobby_update_transaction", "lobby_id"), &DiscordSDKLobbyManager::get_lobby_update_transaction);
	ClassDB::bind_method(D_METHOD("create_lobby", "transaction", "callback"), &DiscordSDKLobbyManager::create_lobby);
	ClassDB::bind_method(D_METHOD("update_lobby", "lobby_id", "transaction", "callback"), &DiscordSDKLobbyManager::update_lobby);
	ClassDB::bind_method(D_METHOD("delete_lobby", "lobby_id", "callback"), &DiscordSDKLobbyManager::delete_lobby);
	ClassDB::bind_method(D_METHOD("connect_lobby_with_activity_secret", "activity_secret", "callback"), &DiscordSDKLobbyManager::connect_lobby_with_activity_secret);
	ClassDB::bind_method(D_METHOD("get_lobby_activity_secret", "lobby_id"), &DiscordSDKLobbyManager::get_lobby_activity_secret);
	ClassDB::bind_method(D_METHOD("disconnect_lobby", "lobby_id", "callback"), &DiscordSDKLobbyManager::disconnect_lobby);
	ClassDB::bind_method(D_METHOD("member_count", "lobby_id"), &DiscordSDKLobbyManager::member_count);
	ClassDB::bind_method(D_METHOD("get_member_user_id", "lobby_id", "index"), &DiscordSDKLobbyManager::get_member_user_id);
	ClassDB::bind_method(D_METHOD("get_member_user", "lobby_id", "user"), &DiscordSDKLobbyManager::get_member_user_id);
	ClassDB::bind_method(D_METHOD("on_lobby_update", "callback"), &DiscordSDKLobbyManager::on_lobby_update);
	ClassDB::bind_method(D_METHOD("on_lobby_delete", "callback"), &DiscordSDKLobbyManager::on_lobby_delete);
	ClassDB::bind_method(D_METHOD("on_member_connect", "callback"), &DiscordSDKLobbyManager::on_member_connect);
	ClassDB::bind_method(D_METHOD("on_member_update", "callback"), &DiscordSDKLobbyManager::on_member_update);
	ClassDB::bind_method(D_METHOD("on_member_disconnect", "callback"), &DiscordSDKLobbyManager::on_member_disconnect);
}


DiscordSDKLobbyTransaction * DiscordSDKLobbyManager::get_lobby_create_transaction() {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);

	discord::LobbyTransaction transaction{};
	DiscordSDK::get_singleton()->core->LobbyManager().GetLobbyCreateTransaction(&transaction);

	return memnew(DiscordSDKLobbyTransaction(transaction));
}

DiscordSDKLobbyTransaction * DiscordSDKLobbyManager::get_lobby_update_transaction(int64_t lobby_id) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);

	discord::LobbyTransaction transaction{};
	DiscordSDK::get_singleton()->core->LobbyManager().GetLobbyUpdateTransaction(lobby_id, &transaction);

	return memnew(DiscordSDKLobbyTransaction(transaction));
}

void DiscordSDKLobbyManager::create_lobby(Ref<DiscordSDKLobbyTransaction> transaction, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().CreateLobby(transaction->lobbyTransaction, [=](discord::Result result, const discord::Lobby &lobby) {
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		args.append(memnew(DiscordSDKLobby(lobby)));
		callback.callv(args);
	});
}

void DiscordSDKLobbyManager::update_lobby(int64_t lobby_id, Ref<DiscordSDKLobbyTransaction> transaction, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().UpdateLobby(lobby_id, transaction->lobbyTransaction, [=](discord::Result result) {
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKLobbyManager::delete_lobby(int64_t lobby_id, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().DeleteLobby(lobby_id, [=](discord::Result result) {
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

void DiscordSDKLobbyManager::connect_lobby_with_activity_secret(String activity_secret, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().ConnectLobbyWithActivitySecret(activity_secret.utf8().get_data(), [=](discord::Result result, const discord::Lobby &lobby) {
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		args.append(memnew(DiscordSDKLobby(lobby)));
		callback.callv(args);
	});
}

String DiscordSDKLobbyManager::get_lobby_activity_secret(int64_t lobby_id) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, "", DISCORD_SDK_ERR_NOT_INIT);

	char secret[128] = {0}; // TODO what's the size??
	DiscordSDK::get_singleton()->core->LobbyManager().GetLobbyActivitySecret(lobby_id, secret);

	return String(secret);
}

void DiscordSDKLobbyManager::disconnect_lobby(int64_t lobby_id, Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().DisconnectLobby(lobby_id, [=](discord::Result result) {
		Array args{};
		args.append(static_cast<DiscordSDK::Result>(result));
		callback.callv(args);
	});
}

int32_t DiscordSDKLobbyManager::member_count(int64_t lobby_id) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, -1, DISCORD_SDK_ERR_NOT_INIT);

	int32_t count;
	DiscordSDK::get_singleton()->core->LobbyManager().MemberCount(lobby_id, &count);

	return count;
}

int64_t DiscordSDKLobbyManager::get_member_user_id(int64_t lobby_id, int32_t index) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, -1, DISCORD_SDK_ERR_NOT_INIT);

	int64_t user_id;
	DiscordSDK::get_singleton()->core->LobbyManager().GetMemberUserId(lobby_id, 0, &user_id);

	return user_id;
}

DiscordSDKUser * DiscordSDKLobbyManager::get_member_user(int64_t lobby_id, int64_t user_id) {
	ERR_FAIL_COND_V_MSG(!DiscordSDK::get_singleton()->core, nullptr, DISCORD_SDK_ERR_NOT_INIT);

	discord::User user{};
	DiscordSDK::get_singleton()->core->LobbyManager().GetMemberUser(lobby_id, user_id, &user);

	return memnew(DiscordSDKUser(user));
}

void DiscordSDKLobbyManager::on_lobby_update(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().OnLobbyUpdate.Connect(
		[=](int64_t lobby_id) {
			Array args{};
			args.append(lobby_id);
			callback.callv(args);
		}
	);
}

void DiscordSDKLobbyManager::on_lobby_delete(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().OnLobbyDelete.Connect(
		[=](int64_t lobby_id, int32_t reason) {
			Array args{};
			args.append(lobby_id);
			args.append(reason);
			callback.callv(args);
		}
	);
}

void DiscordSDKLobbyManager::on_member_connect(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().OnMemberConnect.Connect(
		[=](int64_t lobby_id, int64_t user_id) {
			Array args{};
			args.append(lobby_id);
			args.append(user_id);
			callback.callv(args);
		}
	);
}

void DiscordSDKLobbyManager::on_member_update(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().OnMemberUpdate.Connect(
		[=](int64_t lobby_id, int64_t user_id) {
			Array args{};
			args.append(lobby_id);
			args.append(user_id);
			callback.callv(args);
		}
	);
}

void DiscordSDKLobbyManager::on_member_disconnect(Callable callback) {
	ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	DiscordSDK::get_singleton()->core->LobbyManager().OnMemberDisconnect.Connect(
		[=](int64_t lobby_id, int64_t user_id) {
			Array args{};
			args.append(lobby_id);
			args.append(user_id);
			callback.callv(args);
		}
	);
}

// TODO, all these below

void DiscordSDKLobbyManager::connect_network(int64_t lobby_id) { }

void DiscordSDKLobbyManager::disconnect_network(int64_t lobby_id) { }

void DiscordSDKLobbyManager::flush_network() { }

void DiscordSDKLobbyManager::open_network_channel(int64_t lobby_id, int8_t channel_id, bool reliable) { }

void DiscordSDKLobbyManager::send_network_message(int64_t lobby_id, int64_t user_id, int8_t channel_id, Dictionary data) { }

void DiscordSDKLobbyManager::on_network_message(Callable callback) {
	// ERR_FAIL_COND_MSG(!DiscordSDK::get_singleton()->core, DISCORD_SDK_ERR_NOT_INIT);

	// DiscordSDK::get_singleton()->core->LobbyManager().OnNetworkMessage.Connect(
	// 	[=](int64_t lobby_id, int64_t user_id, int8_t channel_id, int8_t * data, int32_t data_length) {
	// 		Array args{};
	// 		args.append(lobby_id);
	// 		args.append(user_id);
	// 		args.append(channel_id);
	// 		// TODO, how do we handle arbitrary data
	// 		// ^ use JSON serialization, for now
	// 		callback.callv(args);
	// 	}
	// );
}
