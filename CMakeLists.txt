cmake_minimum_required(VERSION 3.16)

project(Layout-Engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

option(BUILD_TEST_APP "Build the test executable" ON)

set(COMPILE_FLAGS
    -Wall
    -Wextra
    -Werror
    -Ofast
    -flto=auto
    -march=native
)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    list(APPEND COMPILE_FLAGS -ggdb3)
endif()


add_library(mylib SHARED
    #TODO: add lib files
)

target_include_directories(mylib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_options(mylib PRIVATE
    ${COMPILE_FLAGS}
)
target_link_libraries(mylib PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    config++
)
set_target_properties(mylib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)


if(BUILD_TEST_APP)
    add_executable(layout-test
        src/main.cpp
    )
    target_compile_options(layout-test PRIVATE
        ${COMPILE_FLAGS}
    )
    target_link_libraries(layout-test PRIVATE
        mylib
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()
