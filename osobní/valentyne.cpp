#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    // Pro Windows nastavíme kódování pro zobrazení čeština a emoji
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    // Barevné kódy ANSI
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";
    const std::string BOLD = "\033[1m";
    const std::string RESET = "\033[0m";
    // Další barvy
    const std::string WHITE = "\033[37m";
    const std::string BLACK = "\033[30m";
    const std::string YELLOW = "\033[33m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN = "\033[36m";
    
    // Jasné varianty barev
    const std::string BRIGHT_RED = "\033[91m";
    const std::string BRIGHT_GREEN = "\033[92m";
    const std::string BRIGHT_YELLOW = "\033[93m";
    const std::string BRIGHT_BLUE = "\033[94m";
    const std::string BRIGHT_MAGENTA = "\033[95m";
    const std::string BRIGHT_CYAN = "\033[96m";
    const std::string BRIGHT_WHITE = "\033[97m";
    
    // Pozadí
    const std::string BG_RED = "\033[41m";
    const std::string BG_GREEN = "\033[42m";
    const std::string BG_YELLOW = "\033[43m";
    const std::string BG_BLUE = "\033[44m";
    const std::string BG_MAGENTA = "\033[45m";
    const std::string BG_CYAN = "\033[46m";
    const std::string BG_WHITE = "\033[47m";
    
    //std::cout << BOLD << BG_GREEN << "Ahoj" << RESET << BRIGHT_CYAN << "Ahoj" << RESET << MAGENTA << "Ahoj" << RESET << std::endl; // Testovací řádek
    std::cout << BOLD << "❤️ Ahoj Lásko ❤️" << RESET << std::endl;
    std::cout << BOLD << "\nDneska máš narozeniny a já mám pro tebe něco " << BRIGHT_CYAN << "speciálního" << RESET << "! 🎁" << std::endl;
    std::cout << BOLD << "Prosím odpověz na následující otázku:" << std::endl;
    
    std::string odpoved;
    bool spravnaOdpoved = false;
    
    while (!spravnaOdpoved) {
        std::cout << BRIGHT_GREEN << BOLD << "\nChceš jít se mnou na rande? " << RESET << "(Ano/Ne): " << RESET;
        std::cin >> odpoved;
        
        if (odpoved == "Ano" || odpoved == "ano") {
            std::cout << MAGENTA << BOLD << "💝 Tak tedy platí! 💝\nBuď připravena v neděli 23.11 v 9:00!\nS sebou si vem: hezké oblečení a hlavně dobrou náladu, protože o vše ostatní se postarám já. 😊\n" << WHITE << "I " << BRIGHT_RED << "love you " << WHITE << "baby ❤️" << RESET << std::endl;
            spravnaOdpoved = true;
        } else if (odpoved == "Ne" || odpoved == "ne") {
            std::cout << RED << "Zkus to prosím znovu... 😢" << RESET << std::endl;
        } else {
            std::cout << BLUE << "Neplatná odpověď, zadej prosím 'Ano' nebo 'Ne'" << RESET << std::endl;
        }
    }
    
    return 0;
}