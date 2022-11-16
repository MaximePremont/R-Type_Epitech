##
## EPITECH PROJECT, 2022
## B-CPP-500-LYN-5-1-rtype-maxime.premont
## File description:
## CMakeLists.txt
##

add_library(network STATIC
        src/UDPClient.cpp
        src/UDPServer.cpp
        src/TCPClient.cpp
        src/DataNet.cpp
        src/Network.cpp
)
target_link_directories(network PUBLIC
    "../boost"
    "../ECS"
)
target_link_libraries(network PUBLIC
    Boost::asio
    Boost::serialization
    ecs
)
target_include_directories(network PUBLIC
    "./includes"
    "../ECS/includes"
    "../ECS/includes/components"
    "../ECS/includes/systems"
    "../boost/libs/archive/include"
    "../boost/libs/serialization/include"
    "../boost/libs/asio/include"
    "../boost/libs/serialization/include/boost/archive/"
)

enable_testing()
add_executable(networkTests
        "tests/datanet_test.cpp"
        "tests/network_test.cpp"
)
target_link_directories(networkTests PUBLIC
    "../boost"
    "../ECS"
)
target_link_libraries(networkTests
    Boost::asio
    GTest::gtest_main
    network
)
target_include_directories(networkTests PUBLIC
    "./includes"
    "../boost/libs/asio/include"
    "../ECS/includes"
    "../ECS/includes/components"
    "../ECS/includes/systems"
    "../googletest/googletest/include"
)

gtest_discover_tests(networkTests)
