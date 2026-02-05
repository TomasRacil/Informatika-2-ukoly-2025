#include <iostream>

int main() 
{
    int vyska;

    std::cout << "Zadejte vysku stromecku: ";
    std::cin >> vyska;

    // Vykresleni stromecku
    for (int i = 0; i < vyska; ++i) {
        int mezery = vyska - i - 1;
        
        // Mezery pred stromeckem
        for (int j = 0; j < mezery; ++j) {
            std::cout << ' ';
        }
        
        // Hvezdicky - pouze obrys
        for (int j = 0; j < 2 * i + 1; ++j) {
            if (j == 0 || j == 2 * i || i == vyska - 1) {
                std::cout << '*';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

    // Vykresleni kmenu
    for (int i = 0; i < vyska/3; ++i) {
        // Mezery pred kmenem
        for (int j = 0; j < vyska - 2; ++j) {
            std::cout << ' ';
        }
        // Kmen sirky 3
        std::cout << "***" << std::endl;
    }

    return 0;
}