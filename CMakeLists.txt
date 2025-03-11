project(lvgltest)
add_executable(lvgltest)

add_subdirectory(lvgl)
target_include_directories(lvgl PUBLIC
    .
)

target_sources(lvgltest PRIVATE
    main.c
)
target_link_libraries(lvgltest
    lvgl
    SDL2
)

