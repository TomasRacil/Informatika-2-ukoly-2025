cmake_minimum_required(VERSION 3.10)
project(Ukol_5)

add_executable(rpg_game 
    main.cpp 
    postava.cpp 
    valecnik.cpp 
    mag.cpp
)

add_executable(mytests 
    test.cpp 
    postava.cpp 
    valecnik.cpp 
    mag.cpp
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(mytests GTest::gtest_main)

target_compile_definitions(mytests PRIVATE __TEST__)

add_test(NAME mytests COMMAND mytests)