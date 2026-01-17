#include <iostream>
#include <tuple>
using namespace std;

tuple<int, int> prohod(int a, int b) {
    return {b, a};
}

int main() {
    int cislo_1 = 3;
    int cislo_2 = 5;

    tie(cislo_1, cislo_2) = prohod(cislo_2, cislo_1); // reuses existing variables

    cout << "Cislo 1: " << cislo_1 << "\n";
    cout << "Cislo 2: " << cislo_2 << "\n";

    return 0;
}