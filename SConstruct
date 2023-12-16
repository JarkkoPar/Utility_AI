#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
# Edit: Added the specialsensors subfolder.
env.Append(CPPPATH=["src/","src/SpecialSensors/","src/SpecialConsiderations", "src/NodeQuerySystem", "src/NodeQuerySystem/SearchSpaces", "src/NodeQuerySystem/SearchCriteria", "src/NodeQuerySystem/SearchSpaces/PointGridSearchSpaces", "src/BehaviourTree"])
sources = Glob("src/*.cpp") + Glob("src/SpecialSensors/*.cpp") + Glob("src/SpecialConsiderations/*.cpp") + Glob("src/NodeQuerySystem/*.cpp") + Glob("src/NodeQuerySystem/SearchSpaces/*.cpp") + Glob("src/NodeQuerySystem/SearchCriteria/*.cpp") + Glob("src/NodeQuerySystem/SearchSpaces/PointGridSearchSpaces/*.cpp") + Glob("src/BehaviourTree/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "demo/addons/utility_ai/bin/libutilityai.{}.{}.framework/libutilityai.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "demo/addons/utility_ai/bin/libutilityai{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
