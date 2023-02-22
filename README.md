# GDExtension for Discord GameSDK

## Description

Addon for Discord integration, built for Godot 4.0 rc3 as a GDExtension

Uses Discord GameSDK version v2.5.6
(At the time of writing, the latest version v3.2.1 had a bug with ClearActivity)

### Todo list:
- linux, macos Github Action workflows

## Features implemented

Only some features are implemented as much of the SDK is deprecated.

- Activity
  - Rich Presence
  - Invites, Ask to Join
  - Register application launch command / steam id
- Relationship
  - Get friends list
- User
  - Get user info, such as name and avatar URL

## How to build

1. Download the [Discord GameSDK](https://discord.com/developers/docs/game-sdk/sdk-starter-guide#step-1-get-the-thing) and copy the libs for your platform(s) from `discord_game_sdk_v2.5.6/lib/x86_64/` to `addons/discord/bin/`
2. Initialize and update the git submodule [godot_cpp](https://github.com/godotengine/godot-cpp) to the commit id that corresponds to your version of Godot. This step is to ensure the C++ bindings match.
3. Build the extension using `scons` [More info here](https://docs.godotengine.org/en/stable/development/compiling/introduction_to_the_buildsystem.html)
4. Copy `addons/` folder into your Godot project

## How to use

After building and copying the the `addons/` folder into your Godot project, the following singletons are available in GDScript

- `Discord`
- `DiscordUserManager`
- `DiscordRelationshipManager`
- `DiscordActivityManager`

### Setup

Initialize Discord using your app id:

    var result = Discord.initialize(1047702455569354813, Discord.NoRequireDiscord)
    if result != Discord.Ok:
        return push_error("Failed to create Discord object")
    
    var discord_ready = true

then run callbacks every tick:

    func _process(_delta):
        if discord_ready:
            Discord.run_callbacks()


Note: you can use lambda functions for callbacks

### Examples

Logging:

    var log_callback = func(log_level, msg):
        print("Discord Log | %d | %s" % [log_level, msg])
    
    Discord.set_log_hook(Discord.Debug, log_callback)

Rich Presence:

    var act = DiscordActivity.new()
    act.state = "Coding Solo"
    act.details = "Writing code"
    DiscordActivityManager.update_activity(act, func (res):
        print(res)
    )

Refer to the Discord GameSDK documentation for details on the functions, structs, and callbacks
