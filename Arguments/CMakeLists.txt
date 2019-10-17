project(Arguments VERSION 0.0.1 LANGUAGES CXX)

include_directories(
    ../include/
    ../json/single_include
)

add_library( ${PROJECT_NAME}
    src/Arguments.cc
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    nlohmann_json
)