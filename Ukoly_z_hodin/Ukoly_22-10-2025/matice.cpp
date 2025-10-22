#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

void vypis_matice(const vector<vector<int>>& matice, int radky, int sloupce) {
    for (int i = 0; i < radky; i++) {
        for (int j = 0; j < sloupce; j++) {
            cout << matice[i][j] << " ";
        }
        cout << endl;
    }
}
vector<vector<int>> secti_matice(const vector<vector<int>>& matice_1, const vector<vector<int>>& matice_2) {
    int radky = matice_1.size();
    int sloupce = matice_1[0].size();
    vector<vector<int>> vysledek(radky, vector<int>(sloupce, 0));

    for (int i = 0; i < radky; i++) {
        for (int j = 0; j < sloupce; j++) {
            vysledek[i][j] = matice_1[i][j] + matice_2[i][j];
        }
    }
    return vysledek;
}
vector<vector<int>> rand_matice(int radky, int sloupce) {
    vector<vector<int>> matice(radky, vector<int>(sloupce, 0));
    srand(time(0));
    for (int i = 0; i < radky; i++) {
        for (int j = 0; j < sloupce; j++) {
            matice[i][j] = rand() % 10;
        }
    }
    return matice;
}

int main() {
    int radky, sloupce;
    cin >> radky >> sloupce;

    if (radky <= 0 || sloupce <= 0) {
        cout << "Počet řádků a sloupců musí být kladné číslo." << endl;
        return 1;
    }
    cout << "Matice 1:" << endl;
    vector<vector<int>> matice_1 = rand_matice(radky, sloupce);
    vector<vector<int>> matice_2 = rand_matice(radky, sloupce);
    vypis_matice(matice_1, radky, sloupce);
    cout << "Matice 2:" << endl;
    cout<<endl;
    vypis_matice(matice_2, radky, sloupce);
    cout << endl;
    secti_matice(matice_1, matice_2);
    cout << "Soucet matic:" << endl;
    vypis_matice(secti_matice(matice_1, matice_2), radky, sloupce);
    return 0;
}
