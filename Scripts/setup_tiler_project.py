import sys
import os

from check_essential_tools import check_essential_tools
from _scripts.base_utils import run, run_binary, rmdir, remove
from _scripts.preset_parser import PresetParser


def setup_tiler_project():
    if not check_essential_tools():
        print("\n")
        return False

    print("Removing build directory...")
    rmdir("build")

    run("conan install .")
    run("conan install . -s build_type=Debug --build missing")

    parser = PresetParser("build/generators/CMakePresets.json")
    parser.load_presets()

    parser.preset('configurePresets[name=="conan-default"].hidden = True')

    parser.preset('configurePresets[name=="conan-debug"].inherits = "conan-default"')
    parser.preset('configurePresets[name=="conan-debug"].cacheVariables.CMAKE_BUILD_TYPE = "Debug"')
    parser.preset('buildPresets[name=="conan-debug"].configurePreset = "conan-debug"')
    parser.preset('testPresets[name=="conan-debug"].configurePreset = "conan-debug"')

    parser.preset('configurePresets[name=="conan-release"].inherits = "conan-default"')
    parser.preset('configurePresets[name=="conan-release"].cacheVariables.CMAKE_BUILD_TYPE = "Release"')
    parser.preset('buildPresets[name=="conan-release"].configurePreset = "conan-release"')
    parser.preset('testPresets[name=="conan-release"].configurePreset = "conan-release"')

    parser.save_presets()

    run("cmake -S . -B build --preset=conan-release -DTL_DEV_MODE=ON")
    run("cmake --build build --preset=conan-release")
    
    print("Removing cmake cache, which may conflict with your IDE.")
    remove("build/CMakeCache.txt")

    # arguments are used in ci-workflow
    if "--no-run" in sys.argv:
        print("\n", "Skipping the run...\n")
    else:
        print("\n======== Runing Tiler Sandbox ========\n")
        if os.path.exists("build/Binary/Release"):
            run_binary("build/Binary/Release/TilerSandbox")
        else:
            run_binary("build/Binary/TilerSandbox")
        print("\n")
        input("Press Enter to exit...")
    
setup_tiler_project()
