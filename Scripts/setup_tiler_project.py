import sys
import os

from check_essential_tools import check_essential_tools
from _scripts.base_utils import run, run_binary, rmdir, remove


def setup_tiler_project():
    if not check_essential_tools():
        print("\n")
        return False

    print("Removing build directory...")
    rmdir("build")

    run("conan install .", True)
    run("conan install . -s build_type=Debug --build missing", True)
    run("cmake -S . -B build -DTL_DEV_MODE=ON -DCMAKE_TOOLCHAIN_FILE=build/generators/conan_toolchain.cmake", True)
    run("cmake --build build --config Release", True)
    
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
