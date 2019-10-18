project(Font VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../../cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    ${sdl2core_sdl2}
    ${sdl2core_img}
    ${sdl2core_ttf}
    ${json}
)

add_library(${PROJECT_NAME} src/Font.cc)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${sdl2core_sdl2}
    PUBLIC ${sdl2core_img}
    PUBLIC ${sdl2core_ttf}
    PUBLIC ${json}
)

target_link_libraries( ${PROJECT_NAME}
    sdl2core::sdl2
    sdl2core::img
    sdl2core::ttf
    ${SDL2_LIBRARY}
    ${SDL2_image_LIBRARY}
    ${SDL2_ttf_LIBRARY}
    nlohmann_json
)