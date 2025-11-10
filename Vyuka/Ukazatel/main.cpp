#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void prehod_cisla(int* a, int* b)
    {
         *a+=*b;
         *b=*a-*b;
         *a-=*b;
    }
/*

void najdi_nejmensi_nejvetsi(int* pole, int velikost_pole, int* nejvetsi, int*)
{

}
*/

int main() {
    /*
    int vek = 30;
    int* pVek = &vek;
    cout << vek;
    cout << *pVek;
    */

    int a = 5;
    int b = 10;

    //prehod_cisla(&a,&b);
    }