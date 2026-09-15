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


add_library(Layout SHARED
    # src/GraphicalHooks/GraphicalHooks.cpp
    # src/GraphicalHooks/SFML.cpp
    src/layout/load.cpp
    src/Section/addElement.cpp
    src/Element/Text.cpp
    src/Element/Image.cpp
    src/Element/Rectangle.cpp
)

target_include_directories(Layout
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)
target_compile_options(Layout PRIVATE
    ${COMPILE_FLAGS}
)
target_link_libraries(Layout PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    config++
)
set_target_properties(Layout PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)


if(BUILD_TEST_APP)
    add_executable(${PROJECT_NAME}
        src/main.cpp
    )
    target_compile_options(${PROJECT_NAME} PRIVATE
        ${COMPILE_FLAGS}
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Layout
    )
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()
