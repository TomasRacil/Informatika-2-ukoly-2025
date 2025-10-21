// 2015 day 1

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


ifstream soubor("to_read.txt");
string radek;

int main() {
    int total_floors = 0;
    int total_characters = 0;
    int negativni_floor = 0;
    bool negativni_found = false;

    if (soubor.is_open()) {
        while (getline(soubor, radek)) {
            for (char ch : radek) {
                if (ch == '(' || ch == ')') {
                    total_characters++;
                }

                if (ch == '(') {
                    total_floors++;
                } else if (ch == ')') {
                    total_floors--;
                }

               if (!negativni_found && total_floors == -1) {
                    negativni_found = true;
                    negativni_floor = total_characters;
                };
            }
        }
    }

    soubor.close();
    cout << "Celkovy pocet podlazi: " << total_floors << " Prvni negativni 1:" << negativni_floor << endl;
}