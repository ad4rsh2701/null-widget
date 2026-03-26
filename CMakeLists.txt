cmake_minimum_required(VERSION 3.10)

project(null-widget LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 17) // ehh
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/Win.cpp
    src/ClockWidget.cpp
    src/utils/fonts.cpp
)

# Using 'WIN32' here is the CMake way of saying "/subsystem:windows"
# Basically: Use WinMain instead of main
add_executable(null-widget WIN32 ${SOURCES})

target_link_libraries(null-widget PRIVATE
    user32
    gdi32
)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(null-widget PRIVATE -Wall -Wextra)
endif()
