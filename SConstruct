#!/usr/bin/env python
import os
import sys

env = SConscript("./godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = [Glob("src/*.cpp"), Glob("src/**/*.cpp")]

# Set library name
env.Append(GDEXTENSION_LIB_NAME="discord")

# Add discord sdk binary
env.Append(LIBS=["discord_game_sdk.dll"])
env.Append(LIBPATH=["addons/discord/bin/"])

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "addons/{}/bin/libgd{}.{}.{}.framework/libgd{}.{}.{}".format(
            env["GDEXTENSION_LIB_NAME"], env["GDEXTENSION_LIB_NAME"], env["platform"], env["target"], env["GDEXTENSION_LIB_NAME"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "addons/{}/bin/libgd{}{}{}".format(env["GDEXTENSION_LIB_NAME"], env["GDEXTENSION_LIB_NAME"], env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
