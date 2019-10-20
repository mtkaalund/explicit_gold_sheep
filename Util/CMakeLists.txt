project(Util CXX)

add_library( ${PROJECT_NAME}
    src/util.cc
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    ${sdl2core_sdl2}
    ../json/single_include
)

target_link_libraries(
    ${PROJECT_NAME}
    nlohmann_json::nlohmann_json
    sdl2core::sdl2
    sdl2core::img
    sdl2core::ttf
    ${SDL2_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}

)