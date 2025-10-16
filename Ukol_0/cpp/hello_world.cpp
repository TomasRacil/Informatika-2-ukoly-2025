// #include "vypocty.h"
#include <iostream>
#include <vector>

std::string hello_world()
{
<<<<<<< HEAD
    return "";
=======
    return "Hello world!";
>>>>>>> refs/remotes/origin/main
}

#ifndef __TEST__ // Add this preprocessor guard
int main()
{
    std::cout << hello_world() << std::endl;
<<<<<<< HEAD
=======

>>>>>>> refs/remotes/origin/main
}
#endif // __TEST__