cmake_minimum_required(VERSION 3.16)
project(Simulations LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)  # or higher if needed
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Configure warnings for MSVC
    add_compile_options(/W4 /WX)
else()
    # Configure warnings for GCC and Clang
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Simulations src/main.cpp)
target_link_libraries(Simulations PRIVATE sfml-graphics)
target_compile_features(Simulations PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET Simulations
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:Simulations>
        VERBATIM)
endif()

install(TARGETS Simulations)