import platform
from _scripts.base_utils import run, is_available, refresh_terminal



def check_essential_tools():

    if not is_available("cmake"):
        print("CMake is not available!")
        print("please download/install CMake from https://cmake.org/download")
        return False

    # for Windows Operating System
    if platform.system() == "Windows":

        if not is_available("conan", "2"):
            print("Conan 2 is not available!")

            if not is_available("pip"):
                print("pip is not available, unable to install Conan")
                return False

            print("Installing Conan through pip...")
            run("pip install conan")
            assert(is_available("conan", "2"), "Conan 2 is not available!")

    # for Linux Operating System
    elif platform.system() == "Linux":

        run("exec bash", False)
        if not is_available("conan", "2"):
            print("Conan 2 is not available!")

            if not is_available("pipx"):
                print("pipx is not available!")
                print("Installing pipx through apt-get...")
                run("sudo apt-get install pipx")
                refresh_terminal()
                assert(is_available("pipx"), "pipx is not available!")

            print("Installing Conan through pipx...")
            run("pipx install conan")
            refresh_terminal()
            assert(is_available("conan"), "conan is not available!")

    # for Darwin Operating System
    elif platform.system() == "Darwin":

        run("exec bash", False)
        if not is_available("conan", "2"):
            print("Conan 2 is not available!")

            if is_available("pipx"):
                print("Installing Conan through pipx...")
                run("pipx install conan")
            else:
                print("Installing Conan through pip...")
                run("pip install conan")
            refresh_terminal()
            assert(is_available("conan", "2"), "Conan 2 is not available!")

    
    return True

