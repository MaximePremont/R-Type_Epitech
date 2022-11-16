##
## EPITECH PROJECT, 2022
## B-CPP-500-LYN-5-1-rtype-maxime.premont
## File description:
## CMakeLists.txt
##

add_executable(r-type_server
    src/main.cpp
    src/Server.cpp
    src/LobbyManager.cpp
    src/Lobby.cpp
)
target_link_directories(r-type_server PUBLIC
    "../libs/boost"
    "../libs/Network"
    "../libs/ECS"
    "../libs/SDL2"
    "../Client"
)
target_link_libraries(r-type_server PUBLIC
    Boost::asio
    Boost::serialization
    network
    ecs
    SDL2main
    SDL2-static
    SDL2_image
)
target_include_directories(r-type_server PUBLIC
    "./includes"
    "../Client/includes"
    "../libs/ECS/includes"
    "../libs/ECS/includes/components"
    "../libs/ECS/includes/systems"
    "../libs"
    "../libs/SDL2/include"
    "../libs/SDL_image"
    "../libs/boost/libs/asio/include"
    "../libs/boost/libs/serialization/include"
    "../libs/Network/includes"
)
install(TARGETS r-type_server DESTINATION bin)

install(DIRECTORY ./assets DESTINATION bin)

enable_testing()
add_executable(serverTests
    tests/hello_test.cpp
)
target_link_libraries(serverTests PUBLIC
    GTest::gtest_main
    Boost::asio
    network
    ecs
    SDL2main
    SDL2-static
    SDL2_image
)
target_include_directories(serverTests PUBLIC
    "./includes"
    "../Client/includes"
    "../libs/ECS/includes"
    "../libs/ECS/includes/components"
    "../libs/ECS/includes/systems"
    "../libs/"
    "../libs/SDL2/include"
    "../libs/SDL_image"
    "../libs/boost/libs/asio/include"
    "../libs/googletest/googletest/include"
)
gtest_discover_tests(serverTests)
