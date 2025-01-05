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

# Option to build SFML from source or use pre-installed version
option(BUILD_FROM_SOURCE "Build SFML from source" OFF)

if(BUILD_FROM_SOURCE)
    # Fetch SFML from GitHub if not already available
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
    )
    FetchContent_MakeAvailable(SFML)
else()
    # Set the path to SFML if pre-built
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML-3.0.0/lib/cmake/SFML")

    # Find the SFML package
    find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System Audio)
endif()

# Collect all .cpp files in the 'view', 'controller', and 'model' folders
file(GLOB_RECURSE MODEL_SRC
    "src/model/*.cpp"
)

file(GLOB_RECURSE CONTROLLER_SRC
    "src/controller/*.cpp"
)

file(GLOB_RECURSE VIEW_SRC
    "src/view/*.cpp"
)

# Add the executable
add_executable(Simulations
    src/main.cpp
    ${VIEW_SRC}
    ${CONTROLLER_SRC}
    ${MODEL_SRC}
)

# Automatically add all subdirectories under src
target_include_directories(Simulations PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SFML_INCLUDE_DIRS}
)

# Link SFML libraries
target_link_libraries(Simulations PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
)

# Copy assets to the output directory after build
add_custom_command(TARGET Simulations POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets" $<TARGET_FILE_DIR:Simulations>/assets
)

# Add installation rules
install(TARGETS Simulations)
