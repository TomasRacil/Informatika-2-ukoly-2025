#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
    int version;
    std::cout << "Vyberte verzi (1 = jednoducha, 2 = pokrocila): ";
    std::cin >> version;

    if (version != 1 && version != 2) {
        std::cerr << "Neplatna verze. Musite zadat 1 nebo 2." << std::endl;
        return 1;
    }

    std::ifstream file("data.txt");
    if (!file.is_open()) {
        std::cerr << "Chyba: Nelze otevrit soubor data.txt" << std::endl;
        return 1;
    }

    std::string line;
    int horizontal = 0;
    int depth = 0;
    int aim = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string command;
        int value;
        iss >> command >> value;

        if (version == 1) {
            // Jednoducha verze
            if (command == "forward") {
                horizontal += value;
            } else if (command == "down") {
                depth += value;
            } else if (command == "up") {
                depth -= value;
            }
        } else {
            // Pokrocila verze
            if (command == "forward") {
                horizontal += value;
                depth += aim * value;
            } else if (command == "down") {
                aim += value;
            } else if (command == "up") {
                aim -= value;
            }
        }
    }

    std::cout << "Horizontalni pozice: " << horizontal << std::endl;
    std::cout << "Hloubka: " << depth << std::endl;
    if (version == 2) {
        std::cout << "Aim: " << aim << std::endl;
    }
    std::cout << "Vysledek (horizontal * depth): " << horizontal * depth << std::endl;

    file.close();
    return 0;
}
