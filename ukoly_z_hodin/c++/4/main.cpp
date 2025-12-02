#include <iostream>

void prehod_cisla(int* a, int* b) {
    int temp = *a;
    *a=  *b;
    *b = temp;
}

int main() {
    int a = 5;
    int b = 3;

    std::cout << a << " " << b <<std::endl;

    prehod_cisla(&a, &b);

    std::cout << a << " " << b <<std::endl;


    //int vek = 30;
    //int* pVek = &vek;

    //std::cout << "" ;
    //std::cout << "" ;

}