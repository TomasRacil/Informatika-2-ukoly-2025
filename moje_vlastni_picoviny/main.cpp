#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

string nazevVolby(int volba) {
    switch (volba) {
        case 1: return "Kámen";
        case 2: return "Nůžky";
        case 3: return "Papír";
        default: return "Neznámé";
    }
}

int vyhodnot(int hrac, int pc) {
    if (hrac == pc) return 0; // remíza
    if ((hrac == 1 && pc == 2) || 
        (hrac == 2 && pc == 3) || 
        (hrac == 3 && pc == 1)) 
        return 1; // hráč vyhrál
    return -1; // počítač vyhrál
}

void vypisVysledek(int hrac, int pc, int vysledek) {
    cout << "Ty: " << nazevVolby(hrac) << "\n";
    cout << "Počítač: " << nazevVolby(pc) << "\n";

    if (vysledek == 0) cout << "Remíza!\n";
    else if (vysledek == 1) cout << "Vyhrál jsi!\n";
    else cout << "Počítač vyhrál!\n";
}

int main() {
   
    srand(time(nullptr)); // inicializace generátoru náhodných čísel
    int hrac, pc, vysledek;
    char znovu;

    do {
        cout << "\n--- KÁMEN / NŮŽKY / PAPÍR ---\n";
        cout << "Zadej svou volbu:\n";
        cout << "1 - Kámen\n2 - Nůžky\n3 - Papír\n> ";
        cin >> hrac;

        if (hrac < 1 || hrac > 3) {
            cout << "Neplatná volba, zkus to znovu!\n";
            continue;
        }

        pc = rand() % 3 + 1;  // náhodná volba 1–3
        vysledek = vyhodnot(hrac, pc);

        vypisVysledek(hrac, pc, vysledek);

        cout << "\nChceš hrát znovu? (y/n): ";
        cin >> znovu;
    } while (znovu == 'y' || znovu == 'Y');

    cout << "\nDíky za hru!\n";
    return 0;
}