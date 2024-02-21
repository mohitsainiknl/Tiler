import sys
import os

from check_essential_tools import check_essential_tools
from _scripts.base_utils import run, run_binary, rmdir, remove


def setup_tiler_project():
    not check_essential_tools()

    print("\nRemoving build directory...")
    rmdir("build")

    if not run("conan profile path default", False):
        run("conan profile detect")

    run("conan install . --build=missing -c tools.system.package_manager:mode=install")

    if "--ci-workflow" in sys.argv:
        print("\n", "Skipping the debug preset creation...\n")
    else:
        run("conan install . -s build_type=Debug --build missing -c tools.system.package_manager:mode=install")
    
    multi_config = os.path.exists("build/generators")
    config_preset = ("conan-default" if multi_config else "conan-release")

    run(f"cmake -S . -B build --preset={config_preset} -DTL_DEV_MODE=ON")
    run("cmake --build build --config release")

    print("Removing cmake cache, which may conflict with your IDE.")
    remove("build/CMakeCache.txt")

    # arguments are used in ci-workflow
    if "--no-run" in sys.argv or "--ci-workflow" in sys.argv:
        print("\n", "Skipping the run...\n")
    else:
        print("\n======== Runing Tiler Sandbox ========\n")
        if multi_config:
            run_binary("build/Binary/Release/TilerSandbox")
        else:
            run_binary("build/Binary/TilerSandbox")
        print("\n")
        input("Press Enter to exit...")
    
setup_tiler_project()
