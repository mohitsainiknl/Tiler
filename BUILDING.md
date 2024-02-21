# Building

## Build With Script

To build this project, you can use the provided scripts: [`setup-tiler-project.bat`](setup-tiler-project.bat) for Windows or [`setup-tiler-project.sh`](setup-tiler-project.sh) for Unix-based systems. 

Before runing script:
- Please close any opened IDE.
- Ensure that you have appropriate permissions set for the `.sh` script by running the following command:
	```bash
	$ chmod +x ./setup_tiler_project.sh
	```

## Build With Commands

Before proceeding:
- Make sure you have `conan` version 2.0.0 or higher installed on your system:
	```bash
	$ conan --version
	```
- default conan profile is present:
	```bash
	$ conan profile detect
	```

Below are the steps to build this project:

### Initial Setup

The first step is to install the required dependencies and generate the files needed by CMake to build the project. You can achieve this using the following commands:
```bash
$ conan install . --build=missing
$ conan install . -s build_type=Debug --build missing
```

The first command installs dependencies with the default `conan-release` preset, while the second command is optional and installs dependencies with the `conan-debug` preset.

> When using libraries like SDL2, it's essential to ensure that the package manager is in `install` mode. To do this, consider using the `-c tools.system.package_manager:mode=install` flag in your installation commands.
### Configure and Build

You can configure and build the project with the following commands:
- For Multi-Config Generators (like - Visual Studio, XCode):
	```bash
	$ cmake -S . -B build --preset=conan-default -DTL_DEV_MODE=ON
	$ cmake --build build --config release
	```
- For Single-Config Generators (like - Makefile, Ninja):
	```bash
	$ cmake -S . -B build --preset=conan-release -DTL_DEV_MODE=ON
	$ cmake --build build --config release
	```

By default, the option `TL_DEV_MODE` is enabled for the `Debug` build.

### Accessing Binaries

After following the above instructions, all binaries will be available in:
- `build/Binary`: for multi-config generators like - Visual Studio, XCode.
- `build/Binary/Release`: for single-config generators like - Makefile, Ninja.

> Please delete the `build/CMakeCache.txt` file before opening this project in any IDE (such as Visual Studio or Xcode). This is particularly important if you're using a multi-configuration generator, as the IDE may attempt to use cached configure settings from previous builds.