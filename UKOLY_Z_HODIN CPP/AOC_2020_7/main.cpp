#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

using Innermap = std::map<std::string, std::string>;
using Rules = std::map<std::string, Innermap>;

Rules pravidla;
std::set<std::string> gold;

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
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
void printRules(){
    for (const auto& pair : pravidla){
        const std::string& outer = pair.first;
        const Innermap& contents = pair.second;
        std::cout << outer << " bags contain: ";
        for (const auto& contentPair : contents){
            const std::string& inner = contentPair.first;
            const std::string& count = contentPair.second;
            std::cout << count << " " << inner << ", ";
        }
        std::cout << std::endl;
    }
}
void find_1(std::string hledany){
    for (const auto& pair : pravidla){
        const std::string& outer = pair.first;
        const Innermap& contents = pair.second;
        for (const auto& contentPair : contents){
            const std::string& inner = contentPair.first;
            if (inner == hledany){
                if (gold.find(outer) == gold.end()){
                    gold.insert(outer);
                    find_1(outer);
                }
            }
        }
    }

}
long long find_2(std::string hledany){
    long long suma = 0;
    for (auto vnitrni : pravidla[hledany]){
        if (vnitrni.first == "other bags."){
             return 0;
        }
        suma += std::stoi(vnitrni.second) * find_2(vnitrni.first);
        suma += std::stoi(vnitrni.second);
    }
    return suma;

}
int main(){
    try{
        parseRules("test.txt");
        printRules();

        //find_1("shiny gold");
        //std::cout << gold.size() << std::endl;
        std::cout << find_2("shiny gold") << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}