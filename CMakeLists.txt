cmake_minimum_required(VERSION 3.10)

project(null-widget LANGUAGES CXX RC)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(CMAKE_CXX_STANDARD 17) #ehh
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

set(SOURCES
    src/Win.cpp
    src/window/ClockWidget.cpp
    src/utils/fonts.cpp
    src/window/ContextMenu.cpp
    resources/resource.rc
)

# Ensuring the font files are there
set(REQUIRED_FONTS
    "${CMAKE_SOURCE_DIR}/resources/fonts/Urbanist.ttf"
    "${CMAKE_SOURCE_DIR}/resources/fonts/Doto.ttf"
    "${CMAKE_SOURCE_DIR}/resources/fonts/KodeMono.ttf"
)
foreach(FONT ${REQUIRED_FONTS})
    if(NOT EXISTS ${FONT})
        message(FATAL_ERROR "COMPILATION ABORTED: Missing font file: ${FONT}")
    endif()
endforeach()

# Using 'WIN32' here is the CMake way of saying "/subsystem:windows"
# Basically: Use WinMain instead of main
add_executable(null-widget WIN32 ${SOURCES})

target_link_libraries(null-widget PRIVATE
    user32
    gdi32
)


if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

    # The "llvm-rc" for the .rc file
    set(CMAKE_RC_COMPILER "llvm-rc")

    target_compile_options(null-widget PRIVATE -Wall -Wextra)

    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(null-widget PRIVATE -O3)
    else()
        target_compile_options(null-widget PRIVATE -O0 -g)
    endif()
endif()
