#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

using namespace std;
using InnerMap = map<string, string>;
using Rules = map<string, InnerMap>;

Rules pravidla;
set<string> gold;

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) return str;
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void parseRules(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Chyba: Soubor nelze otevřít: " + filename);
    }
    string line;
    while (getline(file, line)) {
        size_t containPos = line.find(" bags contain ");
        if (containPos == string::npos) continue;
        string outerKey = line.substr(0, containPos);
        string contentsPart = line.substr(containPos + 14);
        contentsPart.pop_back(); 
        stringstream ssContents(contentsPart);
        string segment;
        while (getline(ssContents, segment, ',')) {
            segment = trim(segment);
            stringstream ssSegment(segment);
            string sCount, adj, color;
            ssSegment >> sCount >> adj >> color;
            if (sCount == "no") {
                pravidla[outerKey]["other bags."] = "no";
            } else {
                string innerKey = adj + " " + color;
                pravidla[outerKey][innerKey] = sCount;
            }
        }
    }
}

void printRules() {
    for (const auto& pair : pravidla) {
        const string& outer = pair.first;
        const InnerMap& contents = pair.second;
        cout << outer << " bags contain: ";
        for (const auto& contentPair : contents) {
            const string& inner = contentPair.first;
            const string& count = contentPair.second;
            cout << count << " " << inner << ", ";
        }
        cout << endl;
    }
}

void find_1(string hledany){
    for (const auto pair : pravidla){
        const string pravidlo = pair.first;
        const InnerMap obsah = pair.second;

        if (obsah.count(hledany)){
            if (gold.find(pravidlo) == gold.end()){
                gold.insert(pravidlo);
                find_1(pravidlo);
            }
        }
    }
}
long long find_2(string hledany){
    long long suma = 0;
    for (auto vnitrni : pravidla [hledany]){
        if (vnitrni.first == "other bags.") 
        continue;
        suma += stoi(vnitrni.second) * find_2(vnitrni.first) + stoi(vnitrni.first);
        suma += stoi(vnitrni.second);
        cout << vnitrni.first << endl;
        cout << vnitrni.second << endl;
    }
    return 0;
}
int main() {
    try {
        parseRules("test.txt");
        printRules();
        find_1("shiny gold");
        //cout << find_1("shiny gold")<<endl;
        cout << gold.size() << endl;
        cout << find_2("shiny gold");
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}