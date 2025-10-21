#include "gtest/gtest.h"
#include "hello_world.cpp" // Předpokládám, že kód je v souboru vypocty.cpp

TEST(TestyFunkci, hello_world)
{
    EXPECT_EQ(hello_world(), "Hello world!");
}