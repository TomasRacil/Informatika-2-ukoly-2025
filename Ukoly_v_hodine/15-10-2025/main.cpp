#include <iostream>
#include <string>
using namespace std;

int main() {
    int volba;

    do {
        cout << "\n=== MENU ===\n";
        cout << "1. Spocitat BMI\n";
        cout << "2. Spocitat BMR\n";
        cout << "3. Konec\n";
        cout << "Vase volba: ";
        cin >> volba;

        switch (volba) {
        case 1: { // Výpočet BMI
            double vaha, vyska, bmi;
            cout << "Zadejte vahu (v kg): ";
            cin >> vaha;
            cout << "Zadejte vysku (v metrech): ";
            cin >> vyska;

            bmi = vaha / (vyska * vyska);
            cout << "Vase BMI je: " << bmi << endl;

            // Slovní hodnocení
            if (bmi < 18.5)
                cout << "Podvaha\n";
            else if (bmi < 25)
                cout << "Normalni hmotnost\n";
            else if (bmi < 30)
                cout << "Nadvaha\n";
            else
                cout << "Obezita\n";

            break;
        }

        case 2: { // Výpočet BMR
            double vaha, vyska, bmr;
            int vek;
            string pohlavi; // použijeme string místo char

            cout << "Zadejte vahu (v kg): ";
            cin >> vaha;
            cout << "Zadejte vysku (v cm): ";
            cin >> vyska;
            cout << "Zadejte vek: ";
            cin >> vek;
            cout << "Zadejte pohlavi (muz / zena): ";
            cin >> pohlavi;

            // malé písmeno pro jistotu
            if (pohlavi == "muz" || pohlavi == "m") {
                bmr = 66.47 + (13.75 * vaha) + (5.003 * vyska) - (6.755 * vek);
            }
            else if (pohlavi == "zena" || pohlavi == "z") {
                bmr = 655.1 + (9.563 * vaha) + (1.850 * vyska) - (4.676 * vek);
            }
            else {
                cout << "Neplatne pohlavi! Zadejte 'muz' nebo 'zena'.\n";
                break;
            }

            cout << "Vas BMR je: " << bmr << " kcal/den\n";
            break;
        }

        case 3:
            cout << "Dekuji za pouziti programu. Nashledanou!\n";
            break;

        default:
            cout << "Neplatna volba! Zadejte cislo 1-3.\n";
            break;
        }

    } while (volba != 3);

    return 0;
}