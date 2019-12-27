project(ResourceHandler VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/../cmake)

find_package(SDL2 REQUIRED)

add_library(${PROJECT_NAME} 
    src/ResourceHandler.cc
)

target_link_libraries(${PROJECT_NAME}
    -lstdc++fs
    ${SDL2_LIBRARY}
    Util
    )

target_include_directories( ${PROJECT_NAME} 
    PUBLIC ${PROJECT_SOURCE_DIR}/include/
    ${sdl2core_sdl2}
    ${Util}
    )