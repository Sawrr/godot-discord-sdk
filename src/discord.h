#ifndef DISCORD_SDK_H
#define DISCORD_SDK_H

#define DISCORD_SDK_ERR_NOT_INIT "Must call Discord.initialize() before calling other functions."

#include "discord-sdk/core.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/callable.hpp>

using namespace godot;

class Discord : public Object {
	GDCLASS(Discord, Object);

	static Discord *singleton;
	discord::Core *core;

protected:
	static void _bind_methods();

public:

	enum CreateFlags {
		Default = 0,
		NoRequireDiscord = 1,
	};

	enum Result {
		Ok = 0,
		ServiceUnavailable = 1,
		InvalidVersion = 2,
		LockFailed = 3,
		InternalError = 4,
		InvalidPayload = 5,
		InvalidCommand = 6,
		InvalidPermissions = 7,
		NotFetched = 8,
		NotFound = 9,
		Conflict = 10,
		InvalidSecret = 11,
		InvalidJoinSecret = 12,
		NoEligibleActivity = 13,
		InvalidInvite = 14,
		NotAuthenticated = 15,
		InvalidAccessToken = 16,
		ApplicationMismatch = 17,
		InvalidDataUrl = 18,
		InvalidBase64 = 19,
		NotFiltered = 20,
		LobbyFull = 21,
		InvalidLobbySecret = 22,
		InvalidFilename = 23,
		InvalidFileSize = 24,
		InvalidEntitlement = 25,
		NotInstalled = 26,
		NotRunning = 27,
		InsufficientBuffer = 28,
		PurchaseCanceled = 29,
		InvalidGuild = 30,
		InvalidEvent = 31,
		InvalidChannel = 32,
		InvalidOrigin = 33,
		RateLimited = 34,
		OAuth2Error = 35,
		SelectChannelTimeout = 36,
		GetGuildTimeout = 37,
		SelectVoiceForceRequired = 38,
		CaptureShortcutAlreadyListening = 39,
		UnauthorizedForAchievement = 40,
		InvalidGiftCode = 41,
		PurchaseError = 42,
		TransactionAborted = 43,
		DrawingInitFailed = 44,
	};

	enum LogLevel {
		Error = 1,
		Warn,
		Info,
		Debug,
	};

	Result initialize(int64_t clientId, CreateFlags flags);
	void set_log_hook(LogLevel logLevel, Callable callback);
	Result run_callbacks();

	static Discord *get_singleton();

	Discord();
	~Discord();
};

VARIANT_ENUM_CAST(Discord, CreateFlags);
VARIANT_ENUM_CAST(Discord, Result);
VARIANT_ENUM_CAST(Discord, LogLevel);

#endif // DISCORD_SDK_H
