#include "discord_sdk.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

Discord *Discord::singleton = nullptr;

Discord * Discord::get_singleton() {
    return singleton;
}

Discord::Discord() {
    core = nullptr;
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

Discord::~Discord() {
    core = nullptr;
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void Discord::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize", "client_id", "flags"), &Discord::initialize);
    ClassDB::bind_method(D_METHOD("set_log_hook", "log_level", "callback"), &Discord::set_log_hook);
    ClassDB::bind_method(D_METHOD("run_callbacks"), &Discord::run_callbacks);

    BIND_ENUM_CONSTANT(Default);
    BIND_ENUM_CONSTANT(NoRequireDiscord);

    BIND_ENUM_CONSTANT(Ok);
    BIND_ENUM_CONSTANT(ServiceUnavailable);
    BIND_ENUM_CONSTANT(InvalidVersion);
    BIND_ENUM_CONSTANT(LockFailed);
    BIND_ENUM_CONSTANT(InternalError);
    BIND_ENUM_CONSTANT(InvalidPayload);
    BIND_ENUM_CONSTANT(InvalidCommand);
    BIND_ENUM_CONSTANT(InvalidPermissions);
    BIND_ENUM_CONSTANT(NotFetched);
    BIND_ENUM_CONSTANT(NotFound);
    BIND_ENUM_CONSTANT(Conflict);
    BIND_ENUM_CONSTANT(InvalidSecret);
    BIND_ENUM_CONSTANT(InvalidJoinSecret);
    BIND_ENUM_CONSTANT(NoEligibleActivity);
    BIND_ENUM_CONSTANT(InvalidInvite);
    BIND_ENUM_CONSTANT(NotAuthenticated);
    BIND_ENUM_CONSTANT(InvalidAccessToken);
    BIND_ENUM_CONSTANT(ApplicationMismatch);
    BIND_ENUM_CONSTANT(InvalidDataUrl);
    BIND_ENUM_CONSTANT(InvalidBase64);
    BIND_ENUM_CONSTANT(NotFiltered);
    BIND_ENUM_CONSTANT(LobbyFull);
    BIND_ENUM_CONSTANT(InvalidLobbySecret);
    BIND_ENUM_CONSTANT(InvalidFilename);
    BIND_ENUM_CONSTANT(InvalidFileSize);
    BIND_ENUM_CONSTANT(InvalidEntitlement);
    BIND_ENUM_CONSTANT(NotInstalled);
    BIND_ENUM_CONSTANT(NotRunning);
    BIND_ENUM_CONSTANT(InsufficientBuffer);
    BIND_ENUM_CONSTANT(PurchaseCanceled);
    BIND_ENUM_CONSTANT(InvalidGuild);
    BIND_ENUM_CONSTANT(InvalidEvent);
    BIND_ENUM_CONSTANT(InvalidChannel);
    BIND_ENUM_CONSTANT(InvalidOrigin);
    BIND_ENUM_CONSTANT(RateLimited);
    BIND_ENUM_CONSTANT(OAuth2Error);
    BIND_ENUM_CONSTANT(SelectChannelTimeout);
    BIND_ENUM_CONSTANT(GetGuildTimeout);
    BIND_ENUM_CONSTANT(SelectVoiceForceRequired);
    BIND_ENUM_CONSTANT(CaptureShortcutAlreadyListening);
    BIND_ENUM_CONSTANT(UnauthorizedForAchievement);
    BIND_ENUM_CONSTANT(InvalidGiftCode);
    BIND_ENUM_CONSTANT(PurchaseError);
    BIND_ENUM_CONSTANT(TransactionAborted);
    BIND_ENUM_CONSTANT(DrawingInitFailed);

    BIND_ENUM_CONSTANT(Error);
    BIND_ENUM_CONSTANT(Warn);
    BIND_ENUM_CONSTANT(Info);
    BIND_ENUM_CONSTANT(Debug);
}

Discord::Result Discord::initialize(int64_t clientId, CreateFlags flags) {
    Discord::Result result = static_cast<Discord::Result>(discord::Core::Create(clientId, flags, &core));
    return result;
    // TODO if bad result, should we set core to nullptr?
}

// TODO should we add is_initialized() method ?

void Discord::set_log_hook(LogLevel logLevel, Callable callback) {
    ERR_FAIL_COND_MSG(!core, DISCORD_SDK_ERR_NOT_INIT);

    core->SetLogHook(static_cast<discord::LogLevel>(logLevel), [=](discord::LogLevel logLevel, const char * msg) {
        Array args;
        args.append(static_cast<LogLevel>(logLevel));
        args.append(msg);
        callback.callv(args);
    });
}

Discord::Result Discord::run_callbacks() {
    ERR_FAIL_COND_V_MSG(!core, static_cast<Discord::Result>(-1), DISCORD_SDK_ERR_NOT_INIT);

    return static_cast<Discord::Result>(core->RunCallbacks());
}
