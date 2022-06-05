from sys import argv
from os import path, walk, makedirs
from shutil import rmtree
from argparse import ArgumentParser
from subprocess import run, PIPE

AS = "tools\\powerpc-eabi-as.exe"
ASFLAGS = "-mgekko -I include"
CC = "tools\\mwcceppc.exe"
CFLAGS = "-I- -i include -ir include/loader -ir include/caddie -ir include/lib -proc gekko -RTTI off -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -msgstyle gcc"
SRC_DIR = "src/"
BUILD_DIR = "build/"
RIIVO_DIR = "riivo/"
EXTERNALS_DIR = "externals/"
BASEROM_DIR = EXTERNALS_DIR + "baserom/"
LOADER_O_DIR = BUILD_DIR + "loader/"
MODULES_DIR = BUILD_DIR + "modules/"

def getLocalPath(path : str, dir : str) -> str:
    idx = path.find(dir)
    if (idx == -1): return path
    return path[idx : ]

def kamekLink(o_files : list, path : str, kamekArgs : str = "") -> None:
    # Create modules directory if necessary
    try:
        makedirs(MODULES_DIR)
    except FileExistsError: pass

    cmd = f"tools\\Kamek.exe {kamekArgs} {' '.join(o_files)} -externals={EXTERNALS_DIR}{args.region}.txt -output-kamek={path} -output-map={path.replace('.bin', '.map')}"
    result = run(cmd, shell=True, stdout=PIPE, stderr=PIPE, universal_newlines=True)
    if (result.returncode != 0):
        print(result.returncode, result.stdout, result.stderr)
        exit()

def compile(path : str) -> None:
    # Manipulate filepaths
    buildPath = path
    if (buildPath.endswith(".cpp")): buildPath = buildPath[0 : len(buildPath) - 4]
    if (buildPath.endswith(".c")): buildPath = buildPath[0 : len(buildPath) - 2]
    buildPath = buildPath.replace("src/", "build/")
    buildPath = ''.join([buildPath, ".o"])
    buildPath = buildPath.replace("/", "\\")
    path = path.replace("/", "\\")

    # Make any required build directories
    try:
        makedirs(buildPath[0 : buildPath.rfind("\\")])
    except FileExistsError: pass

    # Compile
    cmd = f"{CC} {CFLAGS} -c -o {getLocalPath(buildPath, BUILD_DIR)} {getLocalPath(path, SRC_DIR)}"
    result = run(cmd, shell=True, stdout=PIPE, stderr=PIPE, universal_newlines=True)
    if (result.returncode != 0):
        print(result.returncode, result.stdout, result.stderr)
        exit()

def assemble(path : str) -> None:
    # Manipulate filepaths
    buildPath = path
    if (buildPath.endswith(".s")): buildPath = buildPath[0 : len(buildPath) - 2]
    buildPath = buildPath.replace("src/", "build/")
    buildPath = ''.join([buildPath, ".o"])
    buildPath = buildPath.replace("/", "\\")
    path = path.replace("/", "\\")

    # Make any required build directories
    try:
        makedirs(buildPath[0 : buildPath.rfind("\\")])
    except FileExistsError: pass

    # Compile
    cmd = f"{AS} {ASFLAGS} -o {getLocalPath(buildPath, BUILD_DIR)} {getLocalPath(path, SRC_DIR)}"
    result = run(cmd, shell=True, stdout=PIPE, stderr=PIPE, universal_newlines=True)
    if (result.returncode != 0):
        print(result.returncode, result.stdout, result.stderr)
        exit()

if __name__ == "__main__":
    # Support "make clean"
    if (len(argv) == 2 and argv[1].lower() == "clean"):
        rmtree(BUILD_DIR, ignore_errors=True)
        exit()

    # Parse args
    parser = ArgumentParser()
    parser.add_argument("--region", choices=["NTSC_U", "PAL"], required=True, help="Region to build")
    parser.add_argument("--define", required=False, help="Optional user define. Usually NDEBUG")
    parser.add_argument("--flags", required=False, help="Optional extra compiler flags")
    args = parser.parse_args(argv[1:])

    # Chosen region
    CFLAGS = ''.join([CFLAGS, f" -DCADDIE_REGION_{args.region}"])

    # User define
    if (args.define != None): CFLAGS = ''.join([CFLAGS, f" -D{args.define}"])

    # User args
    if (args.flags != None): CFLAGS = ''.join([CFLAGS, f" {args.flags}"])

    # Compile all C/C++ source
    print("Compiling source...")
    for _path, dir, files in walk(SRC_DIR, topdown=True):
        for file in files:
            if (file.endswith(".cpp") or file.endswith(".c")):
                compile(path.join(_path, file))
            if (file.endswith(".s")):
                assemble(path.join(_path, file))

    # Link Kamek loader (DOL patch)
    kamek_o_files = []
    for _path, dir, files in walk(LOADER_O_DIR, topdown=True):
        for file in files:
            if (file.endswith(".o")):
                kamek_o_files.append(path.join(_path, file))
    if (len(kamek_o_files) > 0):
        print("Linking Kamek loader...")
        kamekLink(kamek_o_files, f"build/modules/Loader_{args.region}.bin",
        kamekArgs=f"-static=0x80001900 -input-dol={BASEROM_DIR}baserom_{args.region}.dol -output-dol={BUILD_DIR}main_{args.region}.dol")

    # Link Caddie executable
    game_o_files = []
    for _path, dir, files in walk(BUILD_DIR, topdown=True):
        for file in files:
            if (file.endswith(".o") and "build/loader" not in _path):
                game_o_files.append(path.join(_path, file))
    if (len(game_o_files) > 0):
        print("Linking Caddie executable...")
        kamekLink(game_o_files, f"build/modules/Caddie_{args.region}.bin")

    print("Done!")
