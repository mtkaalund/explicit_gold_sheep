project(GameState VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../cmake)

find_package(SDL2 REQUIRED)

include_directories(
    ${sdl2core_sdl2}
    ../../json/single_include
    ${InputHandler_INCLUDE_DIR}
)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories( ${PROJECT_NAME} INTERFACE include/)