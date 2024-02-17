import os
import platform
import subprocess
import shutil
from contextlib import contextmanager
import time


@contextmanager
def chdir(dir_path):
    current = os.getcwd()
    os.makedirs(dir_path, exist_ok=True)
    os.chdir(dir_path)
    try:
        yield
    finally:
        os.chdir(current)


@contextmanager
def tmp_dir(newdir):
    os.makedirs(newdir)
    try:
        with chdir(newdir):
            yield
    finally:
        shutil.rmtree(newdir)


def rmdir(dir_path):
    shutil.rmtree(dir_path, ignore_errors=True)


def remove(file_path):
    if os.path.exists(file_path):
        os.remove(file_path)


def run(cmd, do_raise=True, should_fail=False):
    print("\nRunning: {}".format(cmd))
    start_time = time.time()

    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True, text=True)

    output = ''
    
    for line in iter(process.stdout.readline, ''):
       print(line, end='', flush=True)
       output += line

    ret = process.wait()

    end_time = time.time()
    elapsed_time = end_time - start_time
    print(f"Elapsed time: {elapsed_time:.2f} seconds")

    if do_raise:
        if ret != 0 and not should_fail:
            raise Exception(f"Failed cmd: {cmd}\n{output}")
        if ret == 0 and should_fail:
            raise Exception(f"Cmd succeeded (failure expected): {cmd}\n{output}")

    return output


def run_binary(file_path):
    command = []
    if platform.system() == "Windows":
        command.append(file_path.replace("/", "\\") + ".exe")
    else:
        command.append("./" + file_path)

    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    for line in iter(process.stdout.readline, b''):
        print(line.decode(), end='')

    process.wait()

    exit_code = process.returncode
    print("Application exited with code:", exit_code)


def refesh_terminal():
    print("Refeshing Terminal...")

    # for Windows Operating System
    if platform.system() == "Windows":
        cmd_out = run("(dir 2>&1 *`|echo CommandPrompt);&<# rem #>echo PowerShell", False)

        if cmd_out.strip() == "PowerShell":
            run("Get-Process -Id $PID | Select-Object -ExpandProperty Path | ForEach-Object { Invoke-Command { & \"$_\" } -NoNewScope }", False)
        else:
            run("refreshenv", False)

    # for Linux and Darwin Operating System
    elif platform.system() == "Linux" or platform.system() == "Darwin":
        cmd_out = run("echo $SHELL", False)

        if cmd_out.strip().endswith("bash"):
            if platform.system() == "Darwin":
                run("source ~/.bash_profile", False)
            else:
                run("source ~/.bashrc", False)

        elif cmd_out.strip().endswith("zsh"):
            run("source ~/.zshrc", False)

        elif cmd_out.strip().endswith("fish"):
            run("source ~/.config/fish/config.fish", False)
        
        else:
            print("Unknown terminal, unable to refesh terminal.")


def is_available(tool, version=""):
    cmd_out = run(tool + " --version", False)

    if version:
        tool += " version " + version
    if cmd_out.lower().startswith(tool.lower()):
        return True
    else:
        return False


def replace(file_path, text, replace):
    with open(file_path, "r") as f:
        content = f.read()
    content2 = content.replace(text, replace)
    assert content != content2
    with open(file_path, "w") as f:
        f.write(content2)


def load(file_path):
    with open(file_path, "r") as f:
        content = f.read()
    return content
