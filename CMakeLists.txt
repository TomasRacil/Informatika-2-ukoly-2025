cmake_minimum_required(VERSION 3.0)
project(Informatika_2)


set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Najdi Google Test framework
enable_testing()
find_package(GTest REQUIRED)
# Propoj test s Google Testem
include_directories(${GTEST_INCLUDE_DIRS})


#Ukol 0
# Add your main executable
add_executable(vypocty ${CMAKE_CURRENT_SOURCE_DIR}/Ukol_0/cpp/hello_world.cpp)
# Add your test executable
add_executable(mytests ${CMAKE_CURRENT_SOURCE_DIR}/Ukol_0/cpp//test.cpp)
target_link_libraries(mytests GTest::gtest_main pthread) 
# Define __TEST__ for the test compilation
target_compile_definitions(mytests PRIVATE __TEST__)
add_test(NAME mytests COMMAND mytests)


#Ukol 3
add_executable(kalkulacka ${CMAKE_CURRENT_SOURCE_DIR}/Ukol_3/main.cpp)