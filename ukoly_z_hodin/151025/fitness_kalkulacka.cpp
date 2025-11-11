#include <iostream>
#include <string>

using namespace std;

int main()
{
    int konec = 0;

    while (konec != 1)
    {
        cout << "Zadejte 1 pro ukonceni programu nebo 0 pro pokracovani: ";
        cin >> konec;

        switch (konec)
        {
        case 0:
            break;
        case 1:
            cout << "Ukoncuji program." << endl;
            return 0;
        default:
            cout << "Neplatna volba, zkuste to znovu." << endl;
            konec = 0;
        }

        int vek, vyska, hmotnost;
        string pohlavi;

        cout << "Vyberte: BMI nebo BMR (zadejte 'bmi' nebo 'bmr'): ";

        string volba;
        cin >> volba;

        cout << "Zadejte svou vysku v cm: ";
        cin >> vyska;
        cout << "Zadejte svou hmotnost v kg: ";
        cin >> hmotnost;

        if (volba == "bmi")
        {
            double bmi = hmotnost / ((vyska / 100.0) * (vyska / 100.0));

            cout << "Ahoj , tve BMI je: " << bmi << endl;
        }
        else if (volba == "bmr")
        {
            cout << "Zadejte svuj vek: ";
            cin >> vek;
            cout << "Zadejte sve pohlavi (muz/zena): ";
            cin >> pohlavi;

            double bmr;

            if (pohlavi == "muz")
            {
                bmr = 88.362 + (13.397 * hmotnost) + (4.799 * vyska) - (5.677 * vek);
            }
            else if (pohlavi == "zena")
            {
                bmr = 447.593 + (9.247 * hmotnost) + (3.098 * vyska) - (4.330 * vek);
            }
            else
            {
                cout << "Neplatne pohlavi." << endl;
                continue;
            }

            cout << "Ahoj , tve BMR je: " << bmr << " kcal/den" << endl;
        }
        else
        {
            cout << "Neplatna volba, zkuste to znovu." << endl;
        }
    }

    return 0;
}
