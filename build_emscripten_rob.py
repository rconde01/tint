import os
import shutil
import subprocess

# prerequisites
# ** Depot Tools **
# https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up
#   ** Windows **
#   https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up
#


if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    depot_tools_path = "D:/dev/tools/depot_tools"
    emsdk_path = "D:/dev/other/emsdk"
    os.environ["PATH"] = f'{depot_tools_path};{os.environ["PATH"]}'
    os.environ["DEPOT_TOOLS_WIN_TOOLCHAIN"] = "0"

    ninja_unix = os.path.join(depot_tools_path,"ninja")

    if os.path.exists(ninja_unix):
        os.rename(ninja_unix,os.path.join(depot_tools_path,"ninja.unix"))

    gclient_file_template = os.path.join(script_dir, "standalone.gclient")
    gclient_file = os.path.join(script_dir, ".gclient")

    orig_dir = os.getcwd()

    if not os.path.exists(gclient_file):
        shutil.copyfile(gclient_file_template, gclient_file)

    subprocess.check_call("gclient sync", shell=True)

    cmake_binary_dir = os.path.join(script_dir, "build")

    os.makedirs(cmake_binary_dir, exist_ok=True)

    try:
        os.chdir(cmake_binary_dir)

        subprocess.check_call(
            f"{emsdk_path}/emsdk_env.bat && emcmake cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release", shell=True)
        
        subprocess.check_call(
            f"{emsdk_path}/emsdk_env.bat && cmake --build .", shell=True)
    finally:
        os.chdir(orig_dir)
