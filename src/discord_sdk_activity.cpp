
#include "discord_sdk_activity.h"

void DiscordSDKActivity::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_application_id"), &DiscordSDKActivity::get_application_id);
    ClassDB::bind_method(D_METHOD("get_name"), &DiscordSDKActivity::get_name);

    ClassDB::bind_method(D_METHOD("set_state", "state"), &DiscordSDKActivity::set_state);
	ClassDB::bind_method(D_METHOD("get_state"), &DiscordSDKActivity::get_state);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "state"), "set_state", "get_state");

    ClassDB::bind_method(D_METHOD("set_details", "details"), &DiscordSDKActivity::set_details);
	ClassDB::bind_method(D_METHOD("get_details"), &DiscordSDKActivity::get_details);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "details"), "set_details", "get_details");

    ClassDB::bind_method(D_METHOD("set_timestamp_start", "time"), &DiscordSDKActivity::set_timestamp_start);
	ClassDB::bind_method(D_METHOD("get_timestamp_start"), &DiscordSDKActivity::get_timestamp_start);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "timestamp_start"), "set_timestamp_start", "get_timestamp_start");

    ClassDB::bind_method(D_METHOD("set_timestamp_end", "time"), &DiscordSDKActivity::set_timestamp_end);
	ClassDB::bind_method(D_METHOD("get_timestamp_end"), &DiscordSDKActivity::get_timestamp_end);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "timestamp_end"), "set_timestamp_end", "get_timestamp_end");

    ClassDB::bind_method(D_METHOD("set_large_image", "image"), &DiscordSDKActivity::set_large_image);
	ClassDB::bind_method(D_METHOD("get_large_image"), &DiscordSDKActivity::get_large_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_image"), "set_large_image", "get_large_image");

    ClassDB::bind_method(D_METHOD("set_large_text", "text"), &DiscordSDKActivity::set_large_text);
	ClassDB::bind_method(D_METHOD("get_large_text"), &DiscordSDKActivity::get_large_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "large_text"), "set_large_text", "get_large_text");

    ClassDB::bind_method(D_METHOD("set_small_image", "image"), &DiscordSDKActivity::set_small_image);
	ClassDB::bind_method(D_METHOD("get_small_image"), &DiscordSDKActivity::get_small_image);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_image"), "set_small_image", "get_small_image");

    ClassDB::bind_method(D_METHOD("set_small_text", "text"), &DiscordSDKActivity::set_small_text);
	ClassDB::bind_method(D_METHOD("get_small_text"), &DiscordSDKActivity::get_small_text);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "small_text"), "set_small_text", "get_small_text");   

    ClassDB::bind_method(D_METHOD("set_party_id", "id"), &DiscordSDKActivity::set_party_id);
	ClassDB::bind_method(D_METHOD("get_party_id"), &DiscordSDKActivity::get_party_id);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "party_id"), "set_party_id", "get_party_id");

    ClassDB::bind_method(D_METHOD("set_party_current_size", "size"), &DiscordSDKActivity::set_party_current_size);
	ClassDB::bind_method(D_METHOD("get_party_current_size"), &DiscordSDKActivity::get_party_current_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "party_current_size"), "set_party_current_size", "get_party_current_size");

    ClassDB::bind_method(D_METHOD("set_party_max_size", "size"), &DiscordSDKActivity::set_party_max_size);
	ClassDB::bind_method(D_METHOD("get_party_max_size"), &DiscordSDKActivity::get_party_max_size);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "party_max_size"), "set_party_max_size", "get_party_max_size");

    ClassDB::bind_method(D_METHOD("set_secret_match", "secret"), &DiscordSDKActivity::set_secret_match);
	ClassDB::bind_method(D_METHOD("get_secret_match"), &DiscordSDKActivity::get_secret_match);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "secret_match"), "set_secret_match", "get_secret_match");

    ClassDB::bind_method(D_METHOD("set_secret_join", "secret"), &DiscordSDKActivity::set_secret_join);
	ClassDB::bind_method(D_METHOD("get_secret_join"), &DiscordSDKActivity::get_secret_join);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "secret_join"), "set_secret_join", "get_secret_join");

    ClassDB::bind_method(D_METHOD("set_secret_spectate", "secret"), &DiscordSDKActivity::set_secret_spectate);
	ClassDB::bind_method(D_METHOD("get_secret_spectate"), &DiscordSDKActivity::get_secret_spectate);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "secret_spectate"), "set_secret_spectate", "get_secret_spectate");

    ClassDB::bind_method(D_METHOD("set_instance", "instance"), &DiscordSDKActivity::set_instance);
	ClassDB::bind_method(D_METHOD("get_instance"), &DiscordSDKActivity::get_instance);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "instance"), "set_instance", "get_instance");
}

int64_t DiscordSDKActivity::get_application_id() {
    return activity.GetApplicationId();
}

String DiscordSDKActivity::get_name() {
    return activity.GetName();
}

String DiscordSDKActivity::get_state() {
    return activity.GetState();
}

void DiscordSDKActivity::set_state(String state) {
    activity.SetState(state.utf8().get_data());
}

String DiscordSDKActivity::get_details() {
    return activity.GetDetails();
}

void DiscordSDKActivity::set_details(String details) {
    activity.SetDetails(details.utf8().get_data());
}

int64_t DiscordSDKActivity::get_timestamp_start() {
    return activity.GetTimestamps().GetStart();
}

void DiscordSDKActivity::set_timestamp_start(int64_t time) {
    activity.GetTimestamps().SetStart(time);
}

int64_t DiscordSDKActivity::get_timestamp_end() {
    return activity.GetTimestamps().GetEnd();
}

void DiscordSDKActivity::set_timestamp_end(int64_t time) {
    activity.GetTimestamps().SetEnd(time);
}

String DiscordSDKActivity::get_large_image() {
    return activity.GetAssets().GetLargeImage();
}

void DiscordSDKActivity::set_large_image(String image) {
    activity.GetAssets().SetLargeImage(image.utf8().get_data());
}

String DiscordSDKActivity::get_large_text() {
    return activity.GetAssets().GetLargeText();
}

void DiscordSDKActivity::set_large_text(String text) {
    activity.GetAssets().SetLargeText(text.utf8().get_data());
}

String DiscordSDKActivity::get_small_image() {
    return activity.GetAssets().GetSmallImage();
}

void DiscordSDKActivity::set_small_image(String image) {
    activity.GetAssets().SetSmallImage(image.utf8().get_data());
}

String DiscordSDKActivity::get_small_text() {
    return activity.GetAssets().GetSmallText();
}

void DiscordSDKActivity::set_small_text(String text) {
    activity.GetAssets().SetSmallText(text.utf8().get_data());
}

String DiscordSDKActivity::get_party_id() {
    return activity.GetParty().GetId();
}

void DiscordSDKActivity::set_party_id(String id) {
    activity.GetParty().SetId(id.utf8().get_data());
}

int32_t DiscordSDKActivity::get_party_current_size() {
    return activity.GetParty().GetSize().GetCurrentSize();
}

void DiscordSDKActivity::set_party_current_size(int32_t size) {
    activity.GetParty().GetSize().SetCurrentSize(size);
}

int32_t DiscordSDKActivity::get_party_max_size() {
    return activity.GetParty().GetSize().GetMaxSize();
}

void DiscordSDKActivity::set_party_max_size(int32_t size) {
    activity.GetParty().GetSize().SetMaxSize(size);
}

String DiscordSDKActivity::get_secret_match() {
    return activity.GetSecrets().GetMatch();
}

void DiscordSDKActivity::set_secret_match(String secret) {
    activity.GetSecrets().SetMatch(secret.utf8().get_data());
}

String DiscordSDKActivity::get_secret_join() {
    return activity.GetSecrets().GetJoin();
}

void DiscordSDKActivity::set_secret_join(String secret) {
    activity.GetSecrets().SetJoin(secret.utf8().get_data());
}

String DiscordSDKActivity::get_secret_spectate() {
    return activity.GetSecrets().GetSpectate();
}

void DiscordSDKActivity::set_secret_spectate(String secret) {
    activity.GetSecrets().SetSpectate(secret.utf8().get_data());
}

bool DiscordSDKActivity::get_instance() {
    return activity.GetInstance();
}

void DiscordSDKActivity::set_instance(bool instance) {
    activity.SetInstance(instance);
}