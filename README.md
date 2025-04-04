Depends on CMake, pkgconf, and SDL2

If using Homebrew:
```brew install pkgconf```
```brew install sdl2```

Compile with
`cmake .`
and then
`make`
or whatever build system thing cmake does on ur os

Make sure to clone this repo recursively using this command: 
```git clone --recurse-submodules -j8 https://github.com/Gaucho-Racing/lvgltesting.git```

If you're on macOS and seeing red squiggly lines around ```#include <SDL2/SDL.h>```, just try building first. It should work; the CMake script will search for SDL2 on your computer. 