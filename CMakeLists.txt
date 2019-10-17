cmake_minimum_required(VERSION 3.5)

project(TileGame CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(sdl2core)
add_subdirectory(Arguments)
add_subdirectory(Util)

include_directories(
    ${sdl2core_sdl2}
    ${sdl2core_img}
    ${Arguments}
    ${Util}
)

#Setting C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cc)

target_link_libraries( ${PROJECT_NAME}
    sdl2core::sdl2
    sdl2core::img
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    Arguments
    Util
)