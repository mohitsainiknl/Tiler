import sys
import os

from check_essential_tools import check_essential_tools
from _scripts.base_utils import run, run_binary, rmdir, remove


def setup_tiler_project():
    not check_essential_tools()

    print("\nRemoving build directory...")
    rmdir("build")

    default_profile = run("conan config home").strip().replace('\\', '/') + "/profiles/default"
    if not os.path.exists(default_profile):
        run("conan profile detect")

    run("conan install . --build=missing")
    run("conan install . -s build_type=Debug --build missing")
    run("cmake -S . -B build --preset=conan-default -DTL_DEV_MODE=ON")
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
