#include <iostream>

using namespace std;

void clearConsole()
{
    cout << "\033[2J\033[1;1H";
}

class Kalkulacka
{
    double vypocetBmi()
    {

        string hmotnost;
        string vyska;

        double vysledek = 0;
        double hmotnostAsDouble = 0;
        double vyskaAsDouble = 0;

    retry:
        try
        {
            cout << "Zadejte vasi hmotnost v kg: \n";
            cin >> hmotnost;
            hmotnostAsDouble = stod(hmotnost);

            cout << "Zadejte vasi vysku v cm: \n";
            cin >> vyska;
            vyskaAsDouble = stod(vyska) / 100;
        }
        catch (...)
        {
            cout << "Neplatny vstup, zkuste to znovu. \n"
                 << endl;
            goto retry;
        }

        vysledek = hmotnostAsDouble / (vyskaAsDouble * vyskaAsDouble);
        return vysledek;
    }

    double vypocetBmr()
    {

        string pohlavi;
        string vek;
        string hmotnost;
        string vyska;

        double vysledek = 0;
        double hmotnostAsDouble = 0;
        double vyskaAsDouble = 0;
        int vekAsInt = 0;

    retry:
        try
        {
            cout << "Zadejte vase pohlavi (m/z): \n";
            cin >> pohlavi;
            if (pohlavi != "m" && pohlavi != "z")
            {
                throw std::exception();
            }

            cout << "Zadejte vas vek: \n";
            cin >> vek;
            vekAsInt = stoi(vek);

            cout << "Zadejte vasi hmotnost v kg: \n";
            cin >> hmotnost;
            hmotnostAsDouble = stod(hmotnost);

            cout << "Zadejte vasi vysku v cm: \n";
            cin >> vyska;
            vyskaAsDouble = stod(vyska);
        }
        catch (...)
        {
            cout << "Neplatny vstup, zkuste to znovu. \n"
                 << endl;
            goto retry;
        }

        // vzorec ktery jsem nasel https://www.thecalculatorsite.com/articles/health/bmr-formula.php

        if (pohlavi == "m")
        {
            vysledek = 66.47 + (13.75 * hmotnostAsDouble) + (5.003 * vyskaAsDouble) - (6.755 * vekAsInt);
        }
        else
            vysledek = 655.1 + (9.563 * hmotnostAsDouble) + (1.85 * vyskaAsDouble) - (4.676 * vekAsInt);

        return vysledek;
    }

public:
    int menu()
    {
    retry:

        cout << "Vyberte si operaci: \n";
        cout << "1. Spocitat BMI \n";
        cout << "2. Spocitat BMR \n";
        cout << "3. Konec" << endl;

        string volba;
        int volbaAsInt = 0;

        cin >> volba;

        try
        {
            volbaAsInt = stoi(volba);
            if (volbaAsInt < 1 || volbaAsInt > 3)
            {
                throw std::out_of_range("Neplatna volba");
            }
        }
        catch (...)
        {
            clearConsole();
            cout << "Neplatna volba, zkuste to znovu." << endl;
            goto retry;
        }
        return volbaAsInt;
    };

    void handleBmi()
    {
        double vysledek = vypocetBmi();
        cout << "Vase BMI je: " << vysledek << endl;

        if (vysledek < 18.5)
        {
            cout << "Podvaha" << endl;
        }
        else if (vysledek >= 18.5 && vysledek < 25)
        {
            cout << "Normalni hmotnost" << endl;
        }
        else if (vysledek >= 25 && vysledek < 30)
        {
            cout << "Nadvaha" << endl;
        }
        else
        {
            cout << "Obezita" << endl;
        }
        cout << "Pro pokracovani stisknete libovolnou klavesu..." << endl;

        // cekani na jakikoliv vstup
        cin.ignore(); // vycisteni bufferu
        cin.get();
    }

    void handleBmr()
    {
        double vysledek = vypocetBmr();
        cout << "Vase BMR je: " << vysledek << endl;
        cout << "Pro pokracovani stisknete libovolnou klavesu..." << endl;

        cin.ignore();
        cin.get();
    }
};

int main()
{
    Kalkulacka k = Kalkulacka();

    cout << "Vitejte v BMI kalkulacce! \n";
    int volba = 0;
    do
    {
        volba = k.menu();
        switch (volba)
        {
        case 1:
            k.handleBmi();
            break;
        case 2:
            k.handleBmr();
            break;
        }
        clearConsole();
    } while (volba != 3);

    cout << "Dekuji za pouziti a nashledanou. \n";

    return 0;
};