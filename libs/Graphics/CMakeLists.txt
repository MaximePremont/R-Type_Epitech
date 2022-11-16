##
## EPITECH PROJECT, 2022
## B-CPP-500-LYN-5-1-rtype-maxime.premont
## File description:
## CMakeLists.txt
##

add_library(graphics STATIC
    src/Graphics.cpp
    src/Loader.cpp
)
target_link_directories(graphics PUBLIC
    ../SDL2
    ../SDL_image
    ../SDL_mixer
)
target_link_libraries(graphics PUBLIC
    SDL2main
    SDL2-static
    SDL2_image
    SDL2_mixer
)
target_include_directories(graphics PUBLIC
    "./includes"
    "../libs/SDL2/include"
    "../libs/SDL_image"
    "../libs/SDL_mixer/include"
)

enable_testing()
add_executable(graphicsTests
    tests/hello_test.cpp
)
target_link_libraries(graphicsTests
    GTest::gtest_main
    graphics
)
target_include_directories(graphicsTests PUBLIC
    "./includes"
    "../googletest/googletest/include"
)

gtest_discover_tests(graphicsTests)