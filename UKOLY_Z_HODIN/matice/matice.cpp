#include <iostream>
#include <ctime>

int** vytvor_nahodnou_matici(int radky, int sloupce){
    int** matice = new int* [radky];
    std::srand(std::time(0));

    for (int i = 0; i < radky; i++) {
        matice[i] = new int[sloupce];
        for (int j = 0; j < sloupce; ++j){
            matice[i][j] = std::rand()%10;
        }

    }
    return matice;
}

void uvolni_matici(int** matice, int radky){
    for (int i = 0; i < radky; ++i){
        delete[] matice[i];
    }
    delete[] matice;
}

void tiskni_pole(int** pole, int radky, int sloupce){
    for (int i = 0; i < radky; ++i){
        for (int j = 0; j < sloupce; ++j){
            std::cout<<pole[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
}

int** secti_matice(int** matice_1, int**matice_2, int radky, int sloupce){
    int** matice = new int* [radky];

    for (int i = 0; i < radky; i++) {
        matice[i] = new int[sloupce];
        for (int j = 0; j < sloupce; ++j){
            matice[i][j] = matice_1[i][j] + matice_2[i][j];
        }

    }
    return matice;
}



int main(){
    int radky, sloupce;
    std::cout<<"Zadej pocet radku: ";
    std::cin>>radky;
    std::cout<<"Zadej pocet sloupců: ";
    std::cin>>sloupce;

    int** matice_1 = vytvor_nahodnou_matici(radky, sloupce);
    int** matice_2 = vytvor_nahodnou_matici(radky, sloupce);

    int** matice_3 = secti_matice(matice_1, matice_2, radky, sloupce);

    std::cout<<"Matice 1: "<<std::endl;
    tiskni_pole(matice_1, radky, sloupce);
    std::cout<<std::endl<<"Matice 1: "<<std::endl;
    tiskni_pole(matice_2, radky, sloupce);
    std::cout<<std::endl<<"Soucet matic: "<<std::endl;
    tiskni_pole(matice_3, radky, sloupce);

    uvolni_matici(matice_1, radky);
    uvolni_matici(matice_2, radky);
    uvolni_matici(matice_3, radky);
    return 0;
}