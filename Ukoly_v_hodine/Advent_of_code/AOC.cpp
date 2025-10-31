#include <iostream>  
#include <string>    
#include <cctype>    

int main() {
    std::string radek;  
    int soucet = 0;     

    
    while (std::getline(std::cin, radek)) {
        char prvni = 0;     
        char posledni = 0;  

        
        for (char znak : radek) {
            if (isdigit(znak)) {     
                if (prvni == 0)      
                    prvni = znak;   
                posledni = znak;     
            }
        }

        
        if (prvni != 0 && posledni != 0) {
            int hodnota = (prvni - '0') * 10 + (posledni - '0'); 
            soucet += hodnota;  
        }
    }

   
    std::cout << soucet << "\n";
}

