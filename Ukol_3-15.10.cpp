#include <iostream>     // tohle řekne C++, že chceme používat příkazy na psaní a čtení z obrazovky (cout a cin)
using namespace std;    // tohle nám dovolí psát jen "cout" místo "std::cout" – zkráceně

int main() {            // tady začíná hlavní část programu, všechno, co se spustí
    int volba;          // vytvoříme si "krabičku" (proměnnou), kam uložíme číslo, které napíšeš do menu

    while (true) {      // "while (true)" znamená: dělej to pořád dokola, dokud neřekneme "break"
        // tady vytiskneme jednoduché menu, co program umí
        cout << "\n1) BMI\n";
        cout << "2) BMR\n";
        cout << "3) Konec\n";
        cout << "Vyber: ";     // vypíšeme výzvu, aby uživatel něco napsal
        cin >> volba;          // počkáme, až napíšeš číslo, a uložíme ho do proměnné "volba"

        // pokud napíšeš 1 → počítáme BMI
        if (volba == 1) {
            double vaha, vyska, bmi;   // double = číslo s desetinnou čárkou
            cout << "Zadej vahu v kg: ";
            cin >> vaha;               // přečteme tvoji váhu
            cout << "Zadej vysku v cm: ";
            cin >> vyska;              // přečteme tvoji výšku

            vyska = vyska / 100;       // přepočítáme výšku z centimetrů na metry (např. 180 → 1.8)
            bmi = vaha / (vyska * vyska);  // použijeme vzorec BMI = váha / (výška²)

            cout << "Tvoje BMI je: " << bmi << endl;   // vypíšeme výsledek

            // podle výsledku napíšeme hodnocení
            if (bmi < 18.5)
                cout << "Mas podvahu.\n";
            else if (bmi < 25)
                cout << "Mas normalni vahu.\n";
            else if (bmi < 30)
                cout << "Mas nadvahu.\n";
            else
                cout << "Mas obezitu.\n";
        }

        // pokud napíšeš 2 → počítáme BMR
        else if (volba == 2) {
            double vaha, vyska, bmr;   // čísla s desetinnou tečkou
            int vek;                   // celé číslo pro věk
            char pohlavi;              // písmeno (M nebo Z)

            cout << "Zadej vahu v kg: ";
            cin >> vaha;
            cout << "Zadej vysku v cm: ";
            cin >> vyska;
            cout << "Zadej vek v letech: ";
            cin >> vek;
            cout << "Zadej pohlavi (M nebo Z): ";
            cin >> pohlavi;

            // pro muže a ženy jsou jiné vzorce
            if (pohlavi == 'M' || pohlavi == 'm')
                bmr = 88.36 + (13.4 * vaha) + (4.8 * vyska) - (5.7 * vek);
            else
                bmr = 447.6 + (9.2 * vaha) + (3.1 * vyska) - (4.3 * vek);

            cout << "Tvoje BMR je asi " << bmr << " kcal za den.\n";
        }

        // pokud napíšeš 3 → ukončíme program
        else if (volba == 3) {
            cout << "Program konci. Ahoj!\n";
            break;     // "break" znamená: skonči smyčku while, tím skončí program
        }

        // pokud napíšeš něco jiného než 1, 2 nebo 3
        else {
            cout << "Zadej cislo 1, 2 nebo 3.\n";
        }
    }

    return 0;   // číslo 0 = všechno proběhlo v pořádku, to se vrací operačnímu systému
}