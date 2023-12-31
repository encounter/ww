import argparse
import sys
import urllib.request
import os
import stat
import platform
from pathlib import Path
import zipfile
import io
import shutil


def dtk_url(tag):
    uname = platform.uname()
    suffix = ""
    system = uname.system.lower()
    if system == "darwin":
        system = "macos"
    elif system == "windows":
        suffix = ".exe"
    arch = uname.machine.lower()
    if arch == "amd64":
        arch = "x86_64"

    repo = "https://github.com/encounter/decomp-toolkit"
    return f"{repo}/releases/download/{tag}/dtk-{system}-{arch}{suffix}"


def sjiswrap_url(tag):
    repo = "https://github.com/encounter/sjiswrap"
    return f"{repo}/releases/download/{tag}/sjiswrap-windows-x86.exe"


def wibo_url(tag):
    repo = "https://github.com/encounter/wibo"
    return f"{repo}/releases/download/{tag}/wibo"


def compilers_url(tag):
    if tag == "1":
        return "https://cdn.discordapp.com/attachments/727918646525165659/1129759991696457728/GC_WII_COMPILERS.zip"
    else:
        sys.exit("Unknown compilers tag %s" % tag)


TOOLS = {
    "dtk": dtk_url,
    "sjiswrap": sjiswrap_url,
    "wibo": wibo_url,
    "compilers": compilers_url,
}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("tool", help="Tool name")
    parser.add_argument("output", type=Path, help="output file path")
    parser.add_argument("--tag", help="GitHub tag", required=True)
    args = parser.parse_args()

    url = TOOLS[args.tool](args.tag)
    output = Path(args.output)

    print(f"Downloading {url} to {output}")
    req = urllib.request.Request(url, headers={"User-Agent": "Mozilla/5.0"})
    with urllib.request.urlopen(req) as response:
        if url.endswith(".zip"):
            data = io.BytesIO(response.read())
            with zipfile.ZipFile(data) as f:
                f.extractall(output)
            output.touch(mode=0o755)
        else:
            with open(output, "wb") as f:
                shutil.copyfileobj(response, f)
            st = os.stat(output)
            os.chmod(output, st.st_mode | stat.S_IEXEC)


if __name__ == "__main__":
    main()
