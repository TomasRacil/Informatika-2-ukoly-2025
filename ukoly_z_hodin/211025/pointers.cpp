#include <iostream>

using namespace std;

void najdi_nejmensi_nejvetsi(int* pole, int velikost_pole, 
    int* nejvetsi, int* nejmensi){

        int* stop = pole + velikost_pole;
        *nejmensi = *pole;
        *nejvetsi = *pole;

        while(!(pole == stop)) {
            if (!nejmensi || *nejmensi > *pole) {
                *nejmensi = *pole;
            }

            if (!nejvetsi || *nejvetsi < *pole) {
                *nejvetsi = *pole;
            }
        }

        /*
        for (int i = 0; i < velikost_pole; i++) {
            int cislo = pole[i];

            if (!nejmensi || *nejmensi > cislo) {
                *nejmensi = cislo;
            }

            if (!nejvetsi || *nejvetsi < cislo) {
                *nejvetsi = cislo;
            }
        }
        */
}

int main(){
    int pole[10]={9,4,6,27,9,2,3,7,5,8};
    int nejmensi;
    int nejvetsi;
    najdi_nejmensi_nejvetsi(pole, 10, &nejvetsi, &nejmensi);

    cout<< nejmensi << ", " << nejvetsi <<std::endl;


    return 0;
}