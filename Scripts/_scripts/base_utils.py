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

    if ret != 0 and not should_fail:
        if do_raise:
            raise Exception(f"Failed cmd: {cmd}\n{output}")
        else:
            return False
    if ret == 0 and should_fail:
        if do_raise:
            raise Exception(f"Cmd succeeded (failure expected): {cmd}\n{output}")
        else:
            return False

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



def is_available(tool, version=""):
    result = run(tool + " --version", False)
    if result:
        if version:
            pos = result.find("version " + version)
            if pos == -1:
                return False
        return True
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
