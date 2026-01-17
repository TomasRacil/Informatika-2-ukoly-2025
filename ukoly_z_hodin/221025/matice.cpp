#include <iostream>
#include <ctime>
#include <string>;

using namespace std;

void print_array(int **pole, int radky, int sloupce)
{
    for (int r = 0; r < radky; r++)
    {
        for (int s = 0; s < sloupce; s++)
        {
            string bez_mod = "";

            if (s != 0 && (sloupce % s) == 0) {
                // cout << "bez mod: " << radky << " r:" << radky % r;
                bez_mod = "\n";
            }

            cout << pole[r][s] << " " << bez_mod;
        }
    }
}

void secist_matice(int **pole_1, int** pole_2, int radky_1, int radky_2, int sloupce_1, int sloupce_2) {
    // int **matice = new int
    cout << "Matice 1: \n:" << endl;
    print_array(pole_1, radky_1, sloupce_1);
    cout << "\nMatice 2: \n:" << endl;
    print_array(pole_2, radky_2, sloupce_2);
    cout << "\nbefore\n" << endl;
    for (int r = 0; r < radky_1; r++) {
        for (int s = 0; s < sloupce_1; s++) {
            pole_1[r][s] += pole_2[r][s];
        }
    }

    print_array(pole_1, radky_1, sloupce_1);
}

int main()
{
    int radky, sloupce;

    cout << "Zadejte pocet radku:";
    cin >> radky;
    cout << "Zadejte pocet sloupcu:";
    cin >> sloupce;

    int **matice_1 = nullptr;
    int **matice_2 = nullptr;

    // alokace pameti
    matice_1 = new int *[radky];
    matice_2 = new int *[radky];

    srand(time(0));

    for (int r = 0; r < radky; r++)
    {
        matice_1[r] = new int[sloupce];
        matice_2[r] = new int[sloupce];

        for (int s = 0; s < sloupce; s++)
        {
            matice_1[r][s] = rand() % 10;
            matice_2[r][s] = rand() % 10;
        }
    }

    secist_matice(matice_1, matice_2, radky, radky, sloupce, sloupce);
}