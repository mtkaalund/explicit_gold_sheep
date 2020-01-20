cmake_minimum_required(VERSION 3.10)

project(TileEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake)

configure_file(${PROJECT_NAME}Config.h.in include/GameObject/${PROJECT_NAME}Config.h)

#Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    ${sdl2core_sdl2}
    ${sdl2core_img}
    ${sdl2core_ttf}
    ${json}
    ${Texture}
    ${Terrain}
)

add_library(${PROJECT_NAME} src/${PROJECT_NAME}.cc)

target_include_directories(
    ${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
#target_include_directories(${PROJECT_NAME}
#    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
#    PRIVATE ${PROJECT_SOURCE_DIR}/include
#    PUBLIC ${sdl2core_sdl2}
#    PUBLIC ${sdl2core_img}
#)

target_link_libraries( ${PROJECT_NAME}
    sdl2core::sdl2
    sdl2core::img
    ${SDL2_LIBRARY}
    ${SDL2_image_LIBRARY}
    nlohmann_json
    Texture
    Terrain
)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES ${PROJECT_NAME}.h ${PROJECT_NAME}Config.h DESTINATION include)