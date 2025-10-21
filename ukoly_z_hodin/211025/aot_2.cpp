#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

ifstream soubor("to_read_text.txt");

int main() {
    if (!soubor || !soubor.is_open()) {
        cerr << "Chyba pri otevirani souboru." << endl;
        return 1;
    }

    // iteruj vsechny radky souboru

    string radek;
    vector<string> cisla;

    while (getline(soubor, radek)) {
        char first_digit = -1;
        char last_digit = -1;

        for (char znak : radek) {

            if (isdigit(znak)) {
                if (first_digit == -1) {
                    first_digit = znak;
                    last_digit = znak;
                } else {
                    last_digit = znak;
                }

                cout << "prvni cislo: " << first_digit << endl;
                cout << "nalezeno cislo: " << last_digit << endl;
            }
        }

        if (first_digit != -1 && last_digit != -1) {
            cisla.push_back(to_string(first_digit + last_digit));
            cout << "pridano cislo: " << first_digit << last_digit << endl;
        }

    }

    int total = 0;
    for (string cislo : cisla) {
       total += stoi(cislo);
    }

    cout << "celkovy soucet: " << total << endl;
}