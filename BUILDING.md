# Building

## Build With Script

To build this project, you can use the provided scripts: [`setup-tiler-project.bat`](setup-tiler-project.bat) for Windows or [`setup-tiler-project.sh`](setup-tiler-project.sh) for Unix-based systems. 

Please ensure that you have appropriate permissions set for the `.sh` script by running the following command:
```bash
$ chmod +x ./setup_tiler_project.sh
```

## Build With Commands

Before proceeding, make sure you have `conan` version 2.0.0 or higher installed on your system. You can verify the installation by running:
```bash
$ conan --version
```

Below are the steps to build this project:

### Initial Setup

The first step is to install the required dependencies and generate the files needed by CMake to build the project. You can achieve this using the following commands:
```bash
$ conan install .
$ conan install . -s build_type=Debug
```

The first command installs dependencies with the default `conan-release` preset, while the second command is optional and installs dependencies with the `conan-debug` preset.

### Configure and Build

You can configure and build the project with the following commands:
```bash
$ cmake -S . -B build -DTL_DEV_MODE=ON
$ cmake --build build --config Release
```

By default, the option `TL_DEV_MODE` is enabled for the `Debug` build.

### Accessing Binaries

After following the above instructions, all binaries will be available in the `build/Binary` directory.

Note: Before opening this project in any IDE (e.g., Visual Studio, Xcode), it is recommended to delete the `build/CMakeCache.txt` file, as IDEs may use their special toolset arguments which could conflict with the default toolset used by CMake.