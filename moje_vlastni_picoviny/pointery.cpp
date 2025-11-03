#include <iostream>
using namespace std;

int main(){
    int radky, sloupce;
    cout << "Zadej pocet radku a sloupcu: " << endl;
    cin >> radky >> sloupce;

    int** matice = new int*[radky];
    for(int i = 0; i < radky; i++){
        matice[i] = new int[sloupce];
    }

    // Uvolnění paměti
    for(int i = 0; i < radky; i++){
        delete[] matice[i];
    }
    delete[] matice;

    return 0;
}