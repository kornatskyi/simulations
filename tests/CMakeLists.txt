# Enables CTest integration
enable_testing()

# Define your test executable, including the source files for the tests
add_executable(unit_tests unit/PhysicsTest.cpp)

# Link against your project's library and Google Test
target_link_libraries(unit_tests PRIVATE gtest_main sfml-graphics)

# Include your project's header files
target_include_directories(unit_tests PRIVATE ../include)

# Discover Google Test tests
include(GoogleTest)
gtest_discover_tests(unit_tests)
