project(SplashState VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../cmake)

find_package(SDL2 REQUIRED)

include_directories(
    ${sdl2core_sdl2}
    ../../json/single_include
    ${GameState_INCLUDE_DIR}
    ${Texture_INCLUDE_DIR}
    ${Font_INCLUDE_DIR}
    ${InputHandler_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} src/SplashState.cc)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include/)

target_link_libraries( ${PROJECT_NAME}
    sdl2core::sdl2
    sdl2core::img
    sdl2core::ttf
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    nlohmann_json
    GameState
    Texture
    Font
    InputHandler
)