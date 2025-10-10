// #include "vypocty.h"
#include <iostream>
#include <vector>

std::string hello_world()
{
    return "Hello world!";
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << hello_world() << std::endl;
}
#endif // __TEST__