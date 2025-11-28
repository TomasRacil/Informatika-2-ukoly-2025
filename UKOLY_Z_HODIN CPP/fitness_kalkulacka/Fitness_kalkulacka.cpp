#include <iostream>
#include <string>
#include <limits>
#include <cmath>
#include <cctype>

using namespace std;

int main() {
    string pohlavi;
    int vek;
    double hmotnost, vyska;
    double bmr, tdee;

    cout << "Zadejte sve pohlavi (muz/zena): ";
    cin >> pohlavi;

    cout << "Zadejte svuj vek: ";
    cin >> vek;

    cout << "Zadejte svou hmotnost v kilogramech: ";
    cin >> hmotnost;

    if (hmotnost <= 0) {
        cerr << "Hmotnost musi byt kladne cislo." << endl;
        return 1;
    }

    cout << "Zadejte svou vysku v metrech: ";
    cin >> vyska;
    if (vyska <= 0) {
        cerr << "Vyska musi byt kladne cislo." << endl;
        return 1;
    }

    while (true) {
        cout << "Pro výpočet BMI zadejte 1 pro výpočet BMR 2 a pro ukonceni 0: ";
        int volba;
        cin >> volba;

   switch (volba) {
        case 0: {
           cout << "Ukoncuji program." << endl;
           return 0;
       }
       case 1: {
           double bmi = hmotnost / (vyska * vyska);
           cout << "Vase BMI je: " << bmi << endl;
           break;
       }
       case 2: {
           if (pohlavi == "muz") {
               bmr = 88.362 + (13.397 * hmotnost) + (4.799 * vyska * 100) - (5.677 * vek);
           } else if (pohlavi == "zena") {
               bmr = 447.593 + (9.247 * hmotnost) + (3.098 * vyska * 100) - (4.330 * vek);
           } else {
               cerr << "Neplatne pohlavi." << endl;
               return 1;
           }
           cout << "Vase BMR je: " << bmr << " kcal/den" << endl;
           break;
       }
       default: {
           cerr << "Neplatna volba." << endl;
           return 1;
       }
   }
        }

   return 0;


}