cmake_minimum_required(VERSION 3.10)

project(Ukol_4)

set(MATRIX_SOURCES
    matrix.cpp
)

add_executable(kalkulacka_oop 
    main.cpp
    ${MATRIX_SOURCES}
)

add_executable(mytests 
    test.cpp
    ${MATRIX_SOURCES}
)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

target_link_libraries(mytests GTest::gtest_main)

target_compile_definitions(mytests PRIVATE __TEST__)

add_test(NAME mytests COMMAND mytests)