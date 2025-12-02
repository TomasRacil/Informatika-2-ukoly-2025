#include <iostream>

int main() 
{
    int vyska;
    int sirka;

    std::cout << "Zadejte vysku stromecku: ";
    std::cin >> vyska;

    //std::cout << "Zadejte sirku stromecku: ";
    //std::cin >> sirka;

    //if (vyska < 2 || sirka < 3 || sirka % 2 == 0) {
    //    std::cout << "Neplatne rozmery stromecku." << std::endl;
    //    return 1;
    //}

    // Vykresleni stromecku
    for (int i = 0; i < vyska; ++i) {
        int mezery = vyska - i - 1;
        int hvezdicky = 2 * i + 1;
        for (int j = 0; j < mezery; ++j) {
            std::cout << ' ';
        }
        for (int j = 0; j < hvezdicky; ++j) {
            std::cout << '*';
        }
        std::cout << std::endl;}
            


}