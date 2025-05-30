# LVGL Testing
## Git Submodules
### First-Time Usage
Clone the repo and the submodules:
```bash
git clone --recurse-submodules https://github.com/Gaucho-Racing/lvgltesting.git
```

<br>

Or if you already cloned the repo and just need the submodules:
```bash
git submodule init
git submodule update --remote
```
### Updating LVGL
```bash
git submodule update --remote
```
## General Notes
For any given board, branch off of `main` to a new branch and make your changes and code work there.

If you're on macOS and seeing red squiggly lines around `#include <SDL2/SDL.h>`, just try building first. It should work; the CMake script will search for SDL2 on your computer. 

## Dependencies
This project depends on CMake, pkgconf, and SDL2. You can optionally use VS Code which will provide a `Launch` configuration.

If using Linux:
```bash
sudo apt install libsdl2-dev pkgconf
```

If using Homebrew:
```zsh
brew install pkgconf
brew install sdl2
```
