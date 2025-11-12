//dynamicka alokace pameti
//alokace 2D pole, predstavme si ze chceme matici ktera ma radky a sloupce
//kazdy radek bude pole
//kazde pole bude mit jine adresy
//udelame si tedy pole pointeru ktera nam da dohromady ty rozsekané pole, do té 2D struktury
//alternativou by bylo kontinuální 1D pole
#include <iostream>
#include <ctime>
using namespace std;

void vytvor_matici(int** pole, int radky, int sloupce){
        for (int i = 0; i < radky; ++i) {
        pole[i] = new int[sloupce];
        for (int j = 0; j < sloupce; ++j){
            pole[i][j] = std::rand()%10;
        }
    }
}

void vypis_pole(int** pole, int radky, int sloupce){
    for(int i = 0; i < radky; i++){
        for(int j = 0; j < sloupce; j++){
            cout << pole[i][j] << "  ";
        }
        cout << endl;
    }
}

void soucet_matice(int** pole, int** matice1, int** matice2, int radky, int sloupce){
        for (int i = 0; i < radky; ++i) {
        pole[i] = new int[sloupce];
        for (int j = 0; j < sloupce; ++j){
            pole[i][j] = matice1[i][j] + matice2[i][j];
        }
    }
}

int main(){
    int radky, sloupce;

    cout << "kolik budes chtit radku";
    cin >> radky;

    cout << "kolik budes chtit sloupcu";
    cin >> sloupce;

    int** matice1 = nullptr;
    int** matice2 = nullptr;
    int** matice3 = nullptr;
    
    matice1 = new int*[radky];
    for(int i = 0; i < radky; i++){
        matice1[i] = new int [sloupce];
    }

    matice2 = new int*[radky];
    for (int i = 0; i < radky; i++){
        matice2[i] = new int [sloupce];
    }

    matice3 = new int*[radky];
    for(int i = 0; i < radky; i++){
        matice3[i] = new int [sloupce];
    }

    srand(time(0));
    cout << "toto je matice 1:" <<endl;
    vytvor_matici(matice1, radky, sloupce);
    vypis_pole(matice1, radky, sloupce);

    cout << "toto je matice 2:"<<endl;
    vytvor_matici(matice2, radky, sloupce);
    vypis_pole(matice2, radky, sloupce);

    cout << "toto je soucet matic" << endl;
    soucet_matice(matice3, matice1, matice2, radky, sloupce);
    vypis_pole(matice3, radky, sloupce);
    return 0;
}