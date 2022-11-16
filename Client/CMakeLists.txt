##
## EPITECH PROJECT, 2022
## B-CPP-500-LYN-5-1-rtype-maxime.premont
## File description:
## CMakeLists.txt
##

add_executable(r-type_client
    src/main.cpp
    src/Game.cpp
    src/PrinterSystem.cpp
)
target_link_directories(r-type_client PUBLIC
    "../libs/boost"
    "../libs/Network"
    "../libs/Graphics"
    "../libs/ECS"
    "../libs/SDL2"
    "../Server"
)
target_link_libraries(r-type_client PUBLIC
    Boost::asio
    network
    ecs
    graphics
    SDL2main
    SDL2-static
    SDL2_image
)
target_include_directories(r-type_client PUBLIC
    "./includes"
    "../libs"
    "../Server/includes"
    "../libs/ECS/includes"
    "../libs/ECS/includes/components"
    "../libs/ECS/includes/systems"
    "../libs/Network/includes"
    "../libs/Graphics/includes"
    "../libs/SDL2/include"
    "../libs/SDL_image"
    "../libs/boost/libs/asio/include"
)
install(TARGETS r-type_client DESTINATION bin)

install(DIRECTORY ./assets DESTINATION bin)

enable_testing()
add_executable(clientTests
    tests/hello_test.cpp
)
target_link_libraries(clientTests PUBLIC
    GTest::gtest_main
    Boost::asio
    network
    ecs
    SDL2main
    SDL2-static
    SDL2_image
)
target_include_directories(clientTests PUBLIC
    "./includes"
    "../Server/includes"
    "../libs/ECS/includes"
    "../libs/ECS/includes/components"
    "../libs/ECS/includes/systems"
    "../libs/Network/includes"
    "../libs/SDL2/include"
    "../libs/SDL_image"
    "../libs/boost/libs/asio/include"
    "../libs/googletest/googletest/include"
)
gtest_discover_tests(clientTests)
