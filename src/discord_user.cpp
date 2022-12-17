
#include "discord_user.h"

void sdk::DiscordUser::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_id", "id"), &sdk::DiscordUser::set_id);
	ClassDB::bind_method(D_METHOD("get_id"), &sdk::DiscordUser::get_id);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

    ClassDB::bind_method(D_METHOD("set_username", "username"), &sdk::DiscordUser::set_username);
	ClassDB::bind_method(D_METHOD("get_username"), &sdk::DiscordUser::get_username);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "username"), "set_username", "get_username");

    ClassDB::bind_method(D_METHOD("set_discriminator", "discriminator"), &sdk::DiscordUser::set_discriminator);
	ClassDB::bind_method(D_METHOD("get_discriminator"), &sdk::DiscordUser::get_discriminator);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "discriminator"), "set_discriminator", "get_discriminator");

    ClassDB::bind_method(D_METHOD("set_avatar", "avatar"), &sdk::DiscordUser::set_avatar);
	ClassDB::bind_method(D_METHOD("get_avatar"), &sdk::DiscordUser::get_avatar);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "avatar"), "set_avatar", "get_avatar");

    ClassDB::bind_method(D_METHOD("set_bot", "bot"), &sdk::DiscordUser::set_bot);
	ClassDB::bind_method(D_METHOD("get_bot"), &sdk::DiscordUser::get_bot);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "bot"), "set_bot", "get_bot");
}

void sdk::DiscordUser::set_id(int64_t id) {
    user.SetId(id);
}

int64_t sdk::DiscordUser::get_id() {
    return user.GetId();
}

void sdk::DiscordUser::set_username(String username) {
    user.SetUsername(username.utf8().get_data());
}

String sdk::DiscordUser::get_username() {
    return String(user.GetUsername());
}

void sdk::DiscordUser::set_discriminator(String discriminator) {
    user.SetDiscriminator(discriminator.utf8().get_data());
}

String sdk::DiscordUser::get_discriminator() {
    return String(user.GetDiscriminator());
}

void sdk::DiscordUser::set_avatar(String avatar) {
    user.SetAvatar(avatar.utf8().get_data());
}

String sdk::DiscordUser::get_avatar() {
    return String(user.GetAvatar());
}

void sdk::DiscordUser::set_bot(bool bot) {
    user.SetBot(bot);
}

bool sdk::DiscordUser::get_bot() {
    return user.GetBot();
}