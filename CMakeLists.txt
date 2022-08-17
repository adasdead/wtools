cmake_minimum_required(VERSION 3.10)
project(WTools VERSION 1.1)

option(COMPILE_JAVA_SOURCES "Compile Java Sources" ON)
option(COMPILE_EXAMPLE "Compile Example" ON)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

if (COMPILE_EXAMPLE)
    add_subdirectory(example)
endif()

if (COMPILE_JAVA_SOURCES)
    add_subdirectory(java)
endif()