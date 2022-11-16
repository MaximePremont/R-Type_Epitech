##
## EPITECH PROJECT, 2022
## B-CPP-500-LYN-5-1-rtype-maxime.premont
## File description:
## CMakeLists.txt
##

cmake_minimum_required(VERSION 3.22)
project(r-type VERSION 2.0)

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(SDL2MIXER_VENDORED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(BUILD_STATIC_LIBRARIES ON)
set(Boost_USE_STATIC_LIBS   ON)
set(SDL2_STATIC ON)

include(AddGitSubmodule.cmake)
include(InstallRequiredSystemLibraries)
include(GoogleTest)

add_git_submodule(libs/SDL2)
add_git_submodule(libs/SDL_image)
add_git_submodule(libs/SDL_mixer)
add_git_submodule(libs/boost)
add_git_submodule(libs/googletest)

add_subdirectory(libs/ECS)
add_subdirectory(libs/Network)
add_subdirectory(libs/Graphics)

add_subdirectory(Server)
add_subdirectory(Client)

file(COPY Client/assets DESTINATION ${CMAKE_BINARY_DIR})

SET(CPACK_RESSOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/License.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR 1)
SET(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_DESCRIPTION "R-type the game of the year")
set(CPACK_PACKAGE_VENDOR "Pocer")
include(CPack)
