#include <iostream>
#include <string>
#include <fstream>

int main ()
{
    std::ifstream vstupniSoubor("data.txt");
    int patro = 0;
    int basementPosition = 0;
    //std::cin >> radek;
    std::string radek;
    if (vstupniSoubor.is_open()) {
        std::getline(vstupniSoubor, radek);
        vstupniSoubor.close();
    }   else {
        std::cerr << "Soubor se nepodarilo otevrit." << std::endl;
        return 1;
    }
    //for (char znak : radek) 
    for (int i = 0; i < radek.length(); i++)
    {
        // std::cout << s[i] << std::endl;
        if (radek[i] == '(') 
        {
            patro++;
        }
        else
        {   
            patro--;
        }
        if(patro==-1){
            basementPosition=i+1;
        }
    }

    std::cout << patro << std::endl;
    std::cout << basementPosition << std::endl;
    return 0;
}