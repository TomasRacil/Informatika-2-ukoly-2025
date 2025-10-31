#include <iostream>
using namespace std;

int main() {
    int vyska_kmnene;
    int vyska_koruny;
    int sirka_kmene;
    int sirka_koruny;
    cout << "Zadejte vysku kmene stromu: ";
    cin >> vyska_kmnene;
    cout << "Zadejte vysku koruny stromu: ";
    cin >> vyska_koruny;
    cout << "Zadejte sirku koruny stromu: ";
    cin >> sirka_koruny;
 for (int i = 0; i < vyska_koruny; i++) {
    for (int j = 0; j < vyska_koruny - i - 1; j++) {
        cout << "-";
    }
    for (int k = 0; k < (2 * i + 1); k++) {
        cout << "*";
    }
    cout << endl;
    }
    /**for (int l = 0; l < vyska_kmnene; l++) {
        for (int m = 0; m < (sirka_koruny - sirka_kmene) / 2; m++) {
            cout << "-";
        }
        for (int n = 0; n < sirka_kmene; n++) {
            cout << "*";
        }
        cout << endl;*/


}

