cmake_minimum_required(VERSION 3.10)
project(ServerLogger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(logger_app
    main.cpp
    logger.cpp
)

enable_testing()
find_package(GTest REQUIRED)

add_executable(tests
    test.cpp
    logger.cpp
)

target_link_libraries(tests GTest::gtest_main)
add_test(NAME LoggerTests COMMAND tests)
