#include <iostream>

int main() {
    int a = 10;
    int* p = &a; // pointer na proměnnou a

    std::cout << "Hodnota a: " << a << std::endl;
    std::cout << "Adresa a: " << &a << std::endl;
    std::cout << "Hodnota přes pointer p: " << *p << std::endl;
    std::cout << "Adresa uložená v pointeru p: " << p << std::endl;

    *p = 20; // změna hodnoty a přes pointer

    std::cout << "Nová hodnota a: " << a << std::endl;

    return 0;
}
