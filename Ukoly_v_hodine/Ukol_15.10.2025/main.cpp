#include <iostream>
using namespace std;

int main()
{
    int volba;
    do {
        cout << "1.Spocitat BMI" << endl;
		cout << "2.Spocitat BMR" << endl;
		cout << "3.Konec" << endl;
		cout << "Vase volba: " << endl;
        cin >> volba;

		switch (volba) {
        case 1: {
            double vyska;
            cout << "Zadejte svoji vysku v cm : ";
            cin >> vyska;
			vyska = vyska / 100;

            double vaha;
            cout << "Zadejte svoji vahu : ";
            cin >> vaha;

            double bmi = vaha / (vyska * vyska);
            if (bmi <= 18.4) {
                cout << "Vase BMI je " << bmi << ", coz znamena ze mate podvahu." << endl;
            }
            else if (bmi > 18.4 && bmi <= 24.9) {
                cout << "Vase BMI je " << bmi << ", coz znamena ze mate normalni vahu." << endl;
            }
            else if (bmi > 24.9 && bmi <= 29.9) {
				cout << "Vase BMI je " << bmi << ", coz znamena ze mate nadvahu." << endl;
            }
            else if (bmi > 30 && bmi <= 34.9) {
                cout << "Vase BMI je " << bmi << ", coz znamena ze mate obezitu." << endl;
            }
            else if (bmi > 35) {
                cout << " Vase BMI je " << bmi << ", coz znamena ze mate tezkou obezitu." << endl;
            }
            break;
        }
            case 2 :
                double vyska;
				cout << "Zadejte svoji vysku v cm : ";
                cin >> vyska;
                
                double vaha;
				cout << "Zadejte svoji vahu : ";
                cin >> vaha;

                int vek;
				cout << "Zadejte svuj vek : ";
				cin >> vek;

				char pohlavi;
				cout << "Zadejte sve pohlavi (m/z) : ";
				cin >> pohlavi;

                if (pohlavi == 'm') {
					double bmr = 88.362 + (13.397 * vaha) + (4.799 * vyska) - (5.677 * vek);
                    cout << "Vase BMR je " << bmr << " kcal/den." << endl;
                }
				else if (pohlavi == 'z') {
                    double bmr = 447.593 + (9.247 * vaha) + (3.098 * vyska) - (4.330 * vek);
                    cout << "Vase BMR je " << bmr << " kcal/den." << endl;
				}
                else {
					cout << "Neplatne pohlavi" << endl;
                }

                break;
            case 3 : 
                cout << "Dekuji za pouziti a nashledanou." << endl;
                break;
            default : 
                cout << "Neplatna volba, zadejte prosim cislo 1-3. " << endl;
				break;
        }
    } while (volba != 3);
}