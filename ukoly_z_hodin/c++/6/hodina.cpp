#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>

int main() {
    int depth = 0;         // tracks depth (affected by up/down)
    int horizontal = 0;    // tracks horizontal position
    std::ifstream file("data.txt");
    
    if (!file.is_open()) {
        std::cout << "Chyba: Soubor se nepodarilo otevrit!" << std::endl;
        return 1;
    }

    std::string radek;
    while (std::getline(file, radek)) {
        std::string command;
        int value;
        std::istringstream iss(radek);
        iss >> command >> value;

        if (command == "up") {
            depth -= value;      // decreases depth
        } else if (command == "forward") {
            horizontal += value; // increases horizontal position
        } else if (command == "down") {
            depth += value;      // increases depth
        }
    }

    std::cout << "Horizontalni pozice (up/down): " << horizontal << std::endl;
    std::cout << "Hloubka: " << depth << std::endl;
    std::cout << "Výsledek (vynasobeny): " << horizontal * depth << std::endl;

    file.close();
    return 0;
}




