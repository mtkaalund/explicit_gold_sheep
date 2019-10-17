cmake_minimum_required(VERSION 3.5)

project(TileGame VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

## External projects
add_subdirectory(json)
## Internal projects
add_subdirectory(sdl2core)
add_subdirectory(Arguments)
add_subdirectory(Util)
add_subdirectory(Texture)

include_directories(
    ${sdl2core_sdl2}
    ${sdl2core_img}
    ${sdl2core_ttf}
    ${NLOHMANN_JSON_INCLUDE_BUILD_DIR}
    ${Arguments}
    ${Util}
    ${Texture}
)

#Setting C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cc)

target_link_libraries( ${PROJECT_NAME}
    sdl2core::sdl2
    sdl2core::img
    sdl2core::ttf
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    nlohmann_json
    Arguments
    Util
    Texture
)