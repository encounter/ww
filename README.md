The Legend of Zelda: The Wind Waker [![Build Status]][actions]
=============

[Build Status]: https://github.com/encounter/ww/actions/workflows/build.yml/badge.svg
[actions]: https://github.com/encounter/ww/actions/workflows/build.yml

This repository supports the following versions:

- GZLE01 - Rev 0 (USA), Rev 48 (Korea)
- GZLP01 - Rev 0 (EUR)
- GZLJ01 - Rev 0 (JPN)

Dependencies
============

Windows:
--------
- Install [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).

macOS:
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):
  ```
  brew install ninja
  ```
- Install [wine-crossover](https://github.com/Gcenx/homebrew-wine):
  ```
  brew install --cask --no-quarantine gcenx/wine/wine-crossover
  ```

Linux:
------
- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).
- Install wine from your package manager.
  - Faster alternative: [WiBo](https://github.com/decompals/WiBo), a minimal 32-bit Windows binary wrapper.  
    Ensure the binary is in `PATH`.

Building
========

- Checkout the repository:
  ```
  git clone https://github.com/encounter/ww.git
  ```
- Download [GC_WII_COMPILERS.zip](https://cdn.discordapp.com/attachments/727918646525165659/1129759991696457728/GC_WII_COMPILERS.zip)
- Extract the archive to `tools/mwcc_compiler`.
  - Resulting structure should be (for example) `tools/mwcc_compiler/GC/1.3.2/mwcceppc.exe`
- Using [Dolphin Emulator](https://dolphin-emu.org/), extract your game to `orig/GLZE01`.  
![](assets/dolphin-extract.png)
  - To save space, the only necessary files are the following. Any others can be deleted.
    - `sys/main.dol`
    - `files/rels/*.rel`
    - `files/RELS.arc`
- Configure:
  ```
  python configure.py
  ```
- Build:
  ```
  ninja
  ```

Diffing
=======

Once the initial build succeeds, an `objdiff.json` should exist in the project root. 

Download the latest release from [encounter/objdiff](https://github.com/encounter/objdiff). Under project settings, set `Project directory`. The configuration should be loaded automatically. 

Select an object from the left sidebar to begin diffing. Changes to the project will rebuild automatically: changes to source files, headers, `configure.py`, `splits.txt` or `symbols.txt`.

![](assets/objdiff.png)