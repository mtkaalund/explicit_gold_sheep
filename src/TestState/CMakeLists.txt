project(TestState VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(
    ${sdl2core_sdl2}
    ${sdl2core_mix}
    ../../json/single_include
    ${GameState_INCLUDE_DIR}
    ${Texture_INCLUDE_DIR}
    ${Font_INCLUDE_DIR}
    ${Util_INCLUDE_DIR}
    ${InputHandler_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} src/TestState.cc)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries( ${PROJECT_NAME}
    sdl2core::sdl2
    sdl2core::img
    sdl2core::ttf
    sdl2core::mix
    ${SDL2_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    nlohmann_json::nlohmann_json
    GameState
    Texture
    Font
    Util
    InputHandler
)