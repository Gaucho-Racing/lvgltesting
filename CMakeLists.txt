project(lvgltest)
cmake_minimum_required(VERSION 3.25)
add_executable(lvgltest)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC
    .
    ${SDL2_INCLUDE_DIRS}
)
target_compile_options(lvgl PUBLIC
    ${SDL2_CFLAGS_OTHER}
)

target_sources(lvgltest PRIVATE
    main.c
    mainGUI.c
)
target_link_libraries(lvgltest
    lvgl
    ${SDL2_LINK_LIBRARIES}
)
target_include_directories(lvgltest PUBLIC
    ${SDL2_INCLUDE_DIRS}
)
target_compile_options(lvgltest PUBLIC
    ${SDL2_CFLAGS_OTHER}
)
