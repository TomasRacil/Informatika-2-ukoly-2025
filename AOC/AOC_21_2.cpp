#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    string cmd;
    int value;
    int horizontal = 0;
    int depth = 0;

    ifstream file("data.txt"); //čte data ze souboru data.txt
    
    while (file >> cmd >> value) {
        if (cmd == "forward") {
            horizontal += value;
        } else if (cmd == "down") {
            depth += value;
        } else if (cmd == "up") {
            depth -= value;
        }
    }

    cout << "Horizontal pozice: " << horizontal << "\n";
    cout << "Hloubka: " << depth << "\n";
    cout << "Výsledek: " << (horizontal * depth) << "\n";

    return 0;
}
