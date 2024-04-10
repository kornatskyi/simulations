cmake_minimum_required(VERSION 3.16)
project(Simulations LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Configure compiler options
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /WX)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/Zi)
    endif()
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-unused-variable -Wno-unused-parameter)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -O0)
    endif()
endif()

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Option for shared libraries
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Main executable
add_executable(Simulations src/main.cpp)
target_include_directories(Simulations PRIVATE include)
target_link_libraries(Simulations PRIVATE sfml-graphics)
target_compile_features(Simulations PRIVATE cxx_std_17)

# Google Test setup for tests subdirectory
include(CTest) # Enables testing capabilities
if(BUILD_TESTING)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # For Windows
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()

# Windows-specific post-build command
if(WIN32)
    add_custom_command(
        TARGET Simulations
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
                $<TARGET_FILE_DIR:Simulations>
        VERBATIM)
endif()

# Installation rules
install(TARGETS Simulations)
