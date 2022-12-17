#!/usr/bin/env python
import os
import sys
from glob import glob
from pathlib import Path

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

# Add discord sdk binary
env.Append(LIBPATH=["addons/discord/bin/"])

if env["platform"] == "windows":
    env.Append(LIBS=["discord_game_sdk.dll"])
else:
    env.Append(LIBS=["discord_game_sdk"])

(extension_path,) = glob("addons/*/*.gdextension")
addon_path = Path(extension_path).parent
project_name = Path(extension_path).stem
debug_or_release = "release" if env["target"] == "template_release" else "template_debug"

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "{0}/bin/libgd{1}.{2}.{3}.framework/{1}.{2}.{3}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "{}/bin/libgd{}.{}.{}.{}{}".format(
            addon_path,
            project_name,
            env["platform"],
            debug_or_release,
            env["arch"],
            env["SHLIBSUFFIX"],
        ),
        source=sources,
    )

Default(library)
