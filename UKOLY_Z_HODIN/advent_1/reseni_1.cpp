#include <iostream>
#include <string>
#include <fstream>

int main() {
    int patro = 0;
    int basement = 0;
    std::ifstream soubor("data.txt");
    std::string radek;
    if (soubor.is_open()) {
        std::getline(soubor, radek);
        soubor.close();
    }
    else {
        std::cerr << "Chyba pri otevirani souboru." << std::endl;
        return 1;
    }
    for (int i=1; i<=radek.length(); i++) {
        if (radek[i] == '(') {
            patro++;
        }
        else {
            patro--;
        }
        if(patro==-1 && basement==0) {
            basement = i+1;
        }
    }
    std::cout << patro << std::endl;
    std::cout << basement << std::endl;
    return 0;