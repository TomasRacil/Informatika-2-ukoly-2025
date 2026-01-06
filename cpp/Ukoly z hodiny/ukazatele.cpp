#include <iostream>

using namespace std;


void prehod_cisla(int* a, int* b){
    *a += *b;
    *b = *a - *b;
    *a -= *b;
}

void najdi_nejmensi_nejvetsi(int* pole, int velikost_pole, int* nejvetsi, int* nejmensi){
    for(int i = 0; i <= 6; i++){
        cout << "hodnota : " << *pole << endl;
        pole++;
    }

}
int main(){
    int pole[7]={9,23,3,5,67,15,8};
    int nejmensi;
    int nejvetsi;
    najdi_nejmensi_nejvetsi(pole, 7, &nejvetsi, &nejmensi);
    
    //int a = 5;
    //int b = 3;
    //prehod_cisla(&a, &b);
    //cout << a << " " << b << endl; 
    
    return 0;
}