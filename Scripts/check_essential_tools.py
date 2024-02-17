import platform
from _scripts.base_utils import run, refesh_terminal, is_available



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
            cmd_out = run("pip install conan")
            refesh_terminal()
            
            if not ("Successfully installed conan" in cmd_out or "Requirement already satisfied" in cmd_out):
                print("Error in installing Conan with pip!")
                print("Mutually download/install Conan from https://github.com/conan-io/conan/releases")
                return False

    # for Linux Operating System
    elif platform.system() == "Linux":

        if not is_available("conan", "2"):
            print("Conan 2 is not available!")

            if not is_available("pipx"):
                print("pipx is not available!")
                print("Installing pipx through apt-get...")
                run("sudo apt-get install pipx")
                refesh_terminal()

            print("Installing Conan through pipx...")
            run("pipx install conan")
            refesh_terminal()

    # for Darwin Operating System
    elif platform.system() == "Darwin":

        if not is_available("conan", "2"):
            print("Conan 2 is not available!")

            print("Installing Conan through brew...")
            run("brew install conan")
            refesh_terminal()

    
    return True

