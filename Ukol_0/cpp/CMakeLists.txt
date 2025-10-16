cmake_minimum_required(VERSION 3.0)
project(Ukol_0)



# Add your main executable
add_executable(vypocty ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.cpp)

# Set the build directory to be a subdirectory of the project directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

# Add your test executable
add_executable(mytests ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

# Najdi Google Test framework
enable_testing()
find_package(GTest REQUIRED)
# Propoj test s Google Testem
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(mytests GTest::gtest_main pthread) 

# Define __TEST__ for the test compilation
target_compile_definitions(mytests PRIVATE __TEST__)

add_test(NAME mytests COMMAND mytests)