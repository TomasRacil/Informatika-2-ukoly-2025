#include "gtest/gtest.h"
#include "hello_world.cpp" // Předpokládám, že kód je v souboru hello_world.cpp

TEST(TestyFunkci, hello_world)
{
    EXPECT_EQ(hello_world(), "Hello world!");
}