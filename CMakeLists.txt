cmake_minimum_required(VERSION 3.16)
project(Simulations LANGUAGES CXX)

include(FetchContent)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure compiler options
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -Wpedantic -Werror -Wno-unused-variable -Wno-unused-parameter)
add_compile_options(-g -O0)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


if(BUILD_FROM_SOURCE)
    # Fetch SFML
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
    )
    FetchContent_MakeAvailable(SFML)
else()
    # Set the path to SFML
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/lib/cmake/SFML")

    # Find the SFML package
    find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System Audio)
endif()


# Main executable
add_executable(Simulations src/main.cpp)

target_include_directories(Simulations PRIVATE include ${SFML_INCLUDE_DIRS})

# Link SFML libraries
target_link_libraries(Simulations PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

# Copy assets over
add_custom_command(TARGET Simulations POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:Simulations>/assets
)

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

# Installation rules
install(TARGETS Simulations)
