
#include "discord_sdk_user.h"

void DiscordSDKUser::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_id", "id"), &DiscordSDKUser::set_id);
	ClassDB::bind_method(D_METHOD("get_id"), &DiscordSDKUser::get_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

    ClassDB::bind_method(D_METHOD("set_username", "username"), &DiscordSDKUser::set_username);
	ClassDB::bind_method(D_METHOD("get_username"), &DiscordSDKUser::get_username);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "username"), "set_username", "get_username");

    ClassDB::bind_method(D_METHOD("set_discriminator", "discriminator"), &DiscordSDKUser::set_discriminator);
	ClassDB::bind_method(D_METHOD("get_discriminator"), &DiscordSDKUser::get_discriminator);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "discriminator"), "set_discriminator", "get_discriminator");

    ClassDB::bind_method(D_METHOD("set_avatar", "avatar"), &DiscordSDKUser::set_avatar);
	ClassDB::bind_method(D_METHOD("get_avatar"), &DiscordSDKUser::get_avatar);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "avatar"), "set_avatar", "get_avatar");

    ClassDB::bind_method(D_METHOD("set_bot", "bot"), &DiscordSDKUser::set_bot);
	ClassDB::bind_method(D_METHOD("get_bot"), &DiscordSDKUser::get_bot);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "bot"), "set_bot", "get_bot");
}

void DiscordSDKUser::set_id(long long id) {
    user.SetId(id);
}

long long DiscordSDKUser::get_id() {
    return user.GetId();
}

void DiscordSDKUser::set_username(String username) {
    user.SetUsername(username.utf8().get_data());
}

String DiscordSDKUser::get_username() {
    return String(user.GetUsername());
}

void DiscordSDKUser::set_discriminator(String discriminator) {
    user.SetDiscriminator(discriminator.utf8().get_data());
}

String DiscordSDKUser::get_discriminator() {
    return String(user.GetDiscriminator());
}

void DiscordSDKUser::set_avatar(String avatar) {
    user.SetAvatar(avatar.utf8().get_data());
}

String DiscordSDKUser::get_avatar() {
    return String(user.GetAvatar());
}

void DiscordSDKUser::set_bot(bool bot) {
    user.SetBot(bot);
}

bool DiscordSDKUser::get_bot() {
    return user.GetBot();
}