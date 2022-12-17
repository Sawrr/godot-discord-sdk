
#include "discord_sdk_activity.h"

void sdk::DiscordActivity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_application_id"), &sdk::DiscordActivity::get_application_id);
    ClassDB::bind_method(D_METHOD("get_name"), &sdk::DiscordActivity::get_name);

    ClassDB::bind_method(D_METHOD("set_state", "state"), &sdk::DiscordActivity::set_state);
	ClassDB::bind_method(D_METHOD("get_state"), &sdk::DiscordActivity::get_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");

    ClassDB::bind_method(D_METHOD("set_details", "details"), &sdk::DiscordActivity::set_details);
	ClassDB::bind_method(D_METHOD("get_details"), &sdk::DiscordActivity::get_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("set_timestamp_start", "time"), &sdk::DiscordActivity::set_timestamp_start);
	ClassDB::bind_method(D_METHOD("get_timestamp_start"), &sdk::DiscordActivity::get_timestamp_start);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "timestamp_start"), "set_timestamp_start", "get_timestamp_start");

    ClassDB::bind_method(D_METHOD("set_timestamp_end", "time"), &sdk::DiscordActivity::set_timestamp_end);
	ClassDB::bind_method(D_METHOD("get_timestamp_end"), &sdk::DiscordActivity::get_timestamp_end);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "timestamp_end"), "set_timestamp_end", "get_timestamp_end");

    ClassDB::bind_method(D_METHOD("set_large_image", "image"), &sdk::DiscordActivity::set_large_image);
	ClassDB::bind_method(D_METHOD("get_large_image"), &sdk::DiscordActivity::get_large_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image"), "set_large_image", "get_large_image");

    ClassDB::bind_method(D_METHOD("set_large_text", "text"), &sdk::DiscordActivity::set_large_text);
	ClassDB::bind_method(D_METHOD("get_large_text"), &sdk::DiscordActivity::get_large_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_text"), "set_large_text", "get_large_text");

    ClassDB::bind_method(D_METHOD("set_small_image", "image"), &sdk::DiscordActivity::set_small_image);
	ClassDB::bind_method(D_METHOD("get_small_image"), &sdk::DiscordActivity::get_small_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image"), "set_small_image", "get_small_image");

    ClassDB::bind_method(D_METHOD("set_small_text", "text"), &sdk::DiscordActivity::set_small_text);
	ClassDB::bind_method(D_METHOD("get_small_text"), &sdk::DiscordActivity::get_small_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_text"), "set_small_text", "get_small_text");   

    ClassDB::bind_method(D_METHOD("set_party_id", "id"), &sdk::DiscordActivity::set_party_id);
	ClassDB::bind_method(D_METHOD("get_party_id"), &sdk::DiscordActivity::get_party_id);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "party_id"), "set_party_id", "get_party_id");

    ClassDB::bind_method(D_METHOD("set_party_current_size", "size"), &sdk::DiscordActivity::set_party_current_size);
	ClassDB::bind_method(D_METHOD("get_party_current_size"), &sdk::DiscordActivity::get_party_current_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "party_current_size"), "set_party_current_size", "get_party_current_size");

    ClassDB::bind_method(D_METHOD("set_party_max_size", "size"), &sdk::DiscordActivity::set_party_max_size);
	ClassDB::bind_method(D_METHOD("get_party_max_size"), &sdk::DiscordActivity::get_party_max_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "party_max_size"), "set_party_max_size", "get_party_max_size");

    ClassDB::bind_method(D_METHOD("set_secret_match", "secret"), &sdk::DiscordActivity::set_secret_match);
	ClassDB::bind_method(D_METHOD("get_secret_match"), &sdk::DiscordActivity::get_secret_match);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "secret_match"), "set_secret_match", "get_secret_match");

    ClassDB::bind_method(D_METHOD("set_secret_join", "secret"), &sdk::DiscordActivity::set_secret_join);
	ClassDB::bind_method(D_METHOD("get_secret_join"), &sdk::DiscordActivity::get_secret_join);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "secret_join"), "set_secret_join", "get_secret_join");

    ClassDB::bind_method(D_METHOD("set_secret_spectate", "secret"), &sdk::DiscordActivity::set_secret_spectate);
	ClassDB::bind_method(D_METHOD("get_secret_spectate"), &sdk::DiscordActivity::get_secret_spectate);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "secret_spectate"), "set_secret_spectate", "get_secret_spectate");

    ClassDB::bind_method(D_METHOD("set_instance", "instance"), &sdk::DiscordActivity::set_instance);
	ClassDB::bind_method(D_METHOD("get_instance"), &sdk::DiscordActivity::get_instance);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "instance"), "set_instance", "get_instance");
}

int64_t sdk::DiscordActivity::get_application_id() {
    return activity.GetApplicationId();
}

String sdk::DiscordActivity::get_name() {
    return activity.GetName();
}

String sdk::DiscordActivity::get_state() {
    return activity.GetState();
}

void sdk::DiscordActivity::set_state(String state) {
    activity.SetState(state.utf8().get_data());
}

String sdk::DiscordActivity::get_details() {
    return activity.GetDetails();
}

void sdk::DiscordActivity::set_details(String details) {
    activity.SetDetails(details.utf8().get_data());
}

int64_t sdk::DiscordActivity::get_timestamp_start() {
    return activity.GetTimestamps().GetStart();
}

void sdk::DiscordActivity::set_timestamp_start(int64_t time) {
    activity.GetTimestamps().SetStart(time);
}

int64_t sdk::DiscordActivity::get_timestamp_end() {
    return activity.GetTimestamps().GetEnd();
}

void sdk::DiscordActivity::set_timestamp_end(int64_t time) {
    activity.GetTimestamps().SetEnd(time);
}

String sdk::DiscordActivity::get_large_image() {
    return activity.GetAssets().GetLargeImage();
}

void sdk::DiscordActivity::set_large_image(String image) {
    activity.GetAssets().SetLargeImage(image.utf8().get_data());
}

String sdk::DiscordActivity::get_large_text() {
    return activity.GetAssets().GetLargeText();
}

void sdk::DiscordActivity::set_large_text(String text) {
    activity.GetAssets().SetLargeText(text.utf8().get_data());
}

String sdk::DiscordActivity::get_small_image() {
    return activity.GetAssets().GetSmallImage();
}

void sdk::DiscordActivity::set_small_image(String image) {
    activity.GetAssets().SetSmallImage(image.utf8().get_data());
}

String sdk::DiscordActivity::get_small_text() {
    return activity.GetAssets().GetSmallText();
}

void sdk::DiscordActivity::set_small_text(String text) {
    activity.GetAssets().SetSmallText(text.utf8().get_data());
}

String sdk::DiscordActivity::get_party_id() {
    return activity.GetParty().GetId();
}

void sdk::DiscordActivity::set_party_id(String id) {
    activity.GetParty().SetId(id.utf8().get_data());
}

int32_t sdk::DiscordActivity::get_party_current_size() {
    return activity.GetParty().GetSize().GetCurrentSize();
}

void sdk::DiscordActivity::set_party_current_size(int32_t size) {
    activity.GetParty().GetSize().SetCurrentSize(size);
}

int32_t sdk::DiscordActivity::get_party_max_size() {
    return activity.GetParty().GetSize().GetMaxSize();
}

void sdk::DiscordActivity::set_party_max_size(int32_t size) {
    activity.GetParty().GetSize().SetMaxSize(size);
}

String sdk::DiscordActivity::get_secret_match() {
    return activity.GetSecrets().GetMatch();
}

void sdk::DiscordActivity::set_secret_match(String secret) {
    activity.GetSecrets().SetMatch(secret.utf8().get_data());
}

String sdk::DiscordActivity::get_secret_join() {
    return activity.GetSecrets().GetJoin();
}

void sdk::DiscordActivity::set_secret_join(String secret) {
    activity.GetSecrets().SetJoin(secret.utf8().get_data());
}

String sdk::DiscordActivity::get_secret_spectate() {
    return activity.GetSecrets().GetSpectate();
}

void sdk::DiscordActivity::set_secret_spectate(String secret) {
    activity.GetSecrets().SetSpectate(secret.utf8().get_data());
}

bool sdk::DiscordActivity::get_instance() {
    return activity.GetInstance();
}

void sdk::DiscordActivity::set_instance(bool instance) {
    activity.SetInstance(instance);
}