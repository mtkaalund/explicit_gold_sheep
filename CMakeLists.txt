cmake_minimum_required(VERSION 3.5)

project(explicit_gold_sheep VERSION 1.0.1 LANGUAGES CXX)

set(BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

## External projects

# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(json)
## Internal projects
add_subdirectory(sdl2core)
add_subdirectory(Arguments)
add_subdirectory(Util)
add_subdirectory(Texture)
add_subdirectory(Font)
add_subdirectory(InputHandler)

add_subdirectory(src/GameState)
add_subdirectory(src/SplashState)
add_subdirectory(src/TestState)

include_directories(
    SYSTEM
    ${sdl2core_sdl2}
    ${sdl2core_img}
    ${sdl2core_ttf}
    ${NLOHMANN_JSON_INCLUDE_BUILD_DIR}
    ${Arguments}
    ${Util}
    ${Texture}
    ${Font}
    ${GameState}
    ${SplashState}
    ${TestState}
)

#Setting C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cc)

target_link_libraries( ${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    SDL2_ttf
    sdl2core::sdl2
    sdl2core::img
    sdl2core::ttf

    nlohmann_json::nlohmann_json
    Arguments
    Util
    Texture
    Font
    GameState
    SplashState
    TestState
)

file(GLOB images
    "res/images/*.png"
    "res/images/*.jpg"
    "res/images/*.jpeg"
)

file(GLOB fonts
    "res/fonts/*.ttf"
)

set(RESOURCE_FILES
    ${images}
    ${fonts}
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RESOURCE "${RESOURCE_FILES}"
)

install(
    TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${BIN_DIR}
    RESOURCE DESTINATION ${BIN_DIR}/res/
)
