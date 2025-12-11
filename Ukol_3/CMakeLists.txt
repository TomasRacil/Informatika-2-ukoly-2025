cmake_minimum_required(VERSION 3.0)
project(Ukol_3)

# Hlavní spustitelný soubor
add_executable(kalkulacka_oop main.cpp)

# Testovací spustitelný soubor
add_executable(mytests test.cpp)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(mytests GTest::gtest_main pthread)

target_compile_definitions(mytests PRIVATE __TEST__)

add_test(NAME mytests COMMAND mytests)
