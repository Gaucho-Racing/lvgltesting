Make sure to clone this repo recursively using this command: <br /> 
```git clone --recurse-submodules -j8 https://github.com/Gaucho-Racing/lvgltesting.git``` <br />

Depends on CMake, pkgconf, and SDL2 <br />

If using Homebrew: <br />
```brew install pkgconf``` <br />
```brew install sdl2``` <br />

Compile with
`cmake .`
and then
`make`
or whatever build system thing cmake does on ur os

If you're on macOS and seeing red squiggly lines around ```#include <SDL2/SDL.h>```, just try building first. It should work; the CMake script will search for SDL2 on your computer. 