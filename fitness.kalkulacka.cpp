#include <iostream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){
    cout << "Vítejte v kalkulačce pro výpočet BMI a BMR, začneme základními údaji" << endl;
            double vyska;
            cout << "Zadejte vaší výšku v metrech: " << endl;
            cin >> vyska;
            double vaha;
            cout << "Zadejte vaší váhu v kilogramech" << endl;
            cin >> vaha;
            
    int volba;
    do {    cout << "Pro možnost výpočtu BMI napiště 1" << endl;
            cout << "Pro možnost výpočtu BMR napiště 2" << endl;
            cout << " Pro ukončení programu napište 3" << endl;
            cin >> volba ;
            cin.fail();
            cin.clear();
            cin.ignore();
            cout << "Neplatna volba, zadejte prosím číslo 1-3." << endl;

        switch (volba) {           
            case 1 :
            double bmi;
            double vyskam2;
            cout << "Vybral/a jste si výpočet BMI" << endl ;
            vyskam2 = vyska * vyska;
            bmi = vaha/vyskam2;
            cout << "Vase aktuální BMI je :" << setprecision(4)<< bmi << endl;
            break;

            case 2 :
            char pohlavi;
            double bmr;
            double vek;
            cout << "Vybral/a jste si výpočet BMR, začneme doplňujícími údaji" << endl;
            cout << "Zadejte věk: " << endl;
            cin >> vek;
            cout << "Zadejte pohlaví M/Z:";
            cin >> pohlavi;
            if (pohlavi == 'M'||'m') {
                bmr = 66.5 + (13.76 * vaha) + (5.003 * vyska * 100 ) - (6.755 * vek);
                cout << "Váš bazální metabolismus je " << bmr << " kcal/den" << endl;
            } 
            else if (pohlavi == 'Z'||'z') {
                bmr = 655 + (9.563 * vaha) + (1.85 * vyska * 100) - (4.676 * vek);
                cout << "Váš bazální metabolismus je " << bmr << " kcal/den" << endl;
            }
            case 3 :
            cout << "https://www.youtube.com/watch?v=Rpyj6T7QBOQ&list=RDRpyj6T7QBOQ&start_radio=1" << endl;
            break;        
        } 

    } while (volba != 3);
}