#include <iostream>
#include <string>
#include <fstream>

int main() {
    std::ifstream soubor("data.txt");
    std::string radek;
    if (!soubor.is_open()) {
        std::cout << "Nepodarilo se otevrit soubor." << std::endl;
    } else {
        while (std::getline(soubor, radek)) {
            std::string cislice;
            for(char znak : radek) {
                if(isdigit(znak)){
                    std::cout << znak;
                    break;
                }
            }
            for(int i=radek.length()-1;i>=0;i--){
                if(isdigit(radek[i])){
                    std::cout << radek[i];
                    break;
                }
            }
            std::cout<<std::endl;
        }

    }
    return 0;
}