project(Arguments CXX)

include_directories(
    ../include/
)

add_library( ${PROJECT_NAME}
    src/Arguments.cc
    )

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)