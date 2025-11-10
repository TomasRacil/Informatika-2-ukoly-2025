#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    ifstream soubor("data2.txt");

    if (!soubor.is_open()) {
        cerr << "Chyba s otevíráním souboru!";
    }

    vector<int> fishes;
    string line;

    while (getline(soubor, line)) {
        stringstream ss(line);
        string temp;

        while (getline(ss, temp, ',')) {
            if (temp.empty()) {
                continue;
            }

            fishes.push_back(stoi(temp));
        }
    }

    int total_days = 256;

    /*
    int timers[0]
    int timers[1]
    int timers[2]
    ...
    
    */
    for (int days = 0; days < total_days; days++) {
        int to_create = 0;

        for (int& fish : fishes) {
            fish--;
            if (fish < 0) {
                fish = 6;
                to_create++;
            }
        }

        for (int new_fish = 0; new_fish < to_create; new_fish++) {
            fishes.push_back(8);
        }
    }

    cout << "new count after: " << total_days << " days is: " << fishes.size() << endl;
}