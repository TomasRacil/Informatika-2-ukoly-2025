#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string cisla [9] = {"one","two","three","four","five","six","seven","eight","nine"};
int preved_na_cislo(string retezec, int pozice){
    for(int i=0; i<9; i++){
        if(retezec.find(cisla[i], pozice)==pozice){
            return i+1;
        }
    }
    return 0;
}

/*int main() {
    std::ifstream soubor("data.txt");
    std::string radek;
    if(!soubor.is_open()) {
        std::cerr << "Nepodarilo se otevrit soubor." << std::endl;
        
    }
    else{
        while (std::getline(soubor, radek)) {
            std::cout << radek << std::endl;
            for (char znak : radek) {
                if(isdigit(znak)) {
                    cislice+=radek[i];
                    break;
                }
            }
        }
            for(int i=radek.length()-1; i>=0; i--){
                if(isdigit(radek[i])) {
            }
        }
    }
}
*/