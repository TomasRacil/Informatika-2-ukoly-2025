#include <iostream>

using namespace std;

int main() {
    int cislo = 125;
    int *p = &cislo;
    int **x = &p;

    **x = 5;
    *p = 200;
    cout << **x << " ::: " << *p << endl;
}