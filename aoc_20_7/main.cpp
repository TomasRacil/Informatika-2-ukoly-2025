#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

using InnerMap = std::map<std::string, std::string>;
using Rules = std::map<std::string, InnerMap>;

Rules pravidla;
std::set<std::string> gold;

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void parseRules(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Chyba: Soubor nelze otevřít: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        size_t containPos = line.find(" bags contain ");
        if (containPos == std::string::npos) continue;
        std::string outerKey = line.substr(0, containPos);
        std::string contentsPart = line.substr(containPos + 14);
        contentsPart.pop_back(); 
        std::stringstream ssContents(contentsPart);
        std::string segment;
        while (std::getline(ssContents, segment, ',')) {
            segment = trim(segment);
            std::stringstream ssSegment(segment);
            std::string sCount, adj, color;
            ssSegment >> sCount >> adj >> color;
            if (sCount == "no") {
                pravidla[outerKey]["other bags."] = "no";
            } else {
                std::string innerKey = adj + " " + color;
                pravidla[outerKey][innerKey] = sCount;
            }
        }
    }
}

void printRules() {
    for (const auto& pair : pravidla) {
        const std::string& outer = pair.first;
        const InnerMap& contents = pair.second;
        std::cout << outer << " bags contain: ";
        for (const auto& contentPair : contents) {
            const std::string& inner = contentPair.first;
            const std::string& count = contentPair.second;
            std::cout << count << " " << inner << ", ";
        }
        std::cout << std::endl;
    }
}

bool find_1(const std::string& target) {
    bool found = false;

    for (const auto& [outer, innerMap] : pravidla) {
        // Pro každou tašku zkontroluj, jestli obsahuje target
        for (const auto& [inner, count] : innerMap) {
            if (inner == target) {
                // našli jsme target uvnitř outer
                if (gold.insert(outer).second) { 
                    // přidáme do množiny jen pokud tam ještě není
                    find_1(outer); // rekurzivně hledáme, kdo obsahuje tuto barvu
                }
                found = true;
            }
        }
    }

    return found;
}



int main() {
    try {
        parseRules("test.txt");
        printRules();

        std::cout<<find_1("shiny gold")<<std::endl;
        std::cout << gold.size() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}