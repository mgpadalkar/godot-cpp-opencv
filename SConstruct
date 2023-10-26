#!/usr/bin/env python
import os
import sys

env = SConscript("./godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

# opencv include and libs from pkg-config
opencv_include = os.popen("echo `pkg-config --cflags opencv`").read().split()
opencv_libs = os.popen("echo `pkg-config --libs opencv`").read().split()

# append opencv_include and opencv_libs appropriately
env.Append(CPPPATH=[p[2:] for p in opencv_include])
env.Append(LIBPATH=[opencv_libs[0][2:]])
env.Append(LIBS=[p[2:] for p in opencv_libs[1:]])

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/bin/libgd_opencv_example.{}.{}.framework/libgd_opencv_example.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/bin/libgd_opencv_example{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
