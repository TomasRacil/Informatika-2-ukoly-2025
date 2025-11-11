#include <iostream> 
#include <string>
#include <cmath>

using namespace std;

int main() {
    cout << "Zadejte sirku stromu: ";
    int sirka_stromu;
    cin >> sirka_stromu;  
    cout << "Zadejte vysku stromku: ";
    int vyska_stromu;
    cin >> vyska_stromu;
    cout << "Zadejte sirku kmene: ";
    int sirka_kmene;
    cin >> sirka_kmene;  
    cout << "Zadejte vysku kmene: ";
    int vyska_kmene;
    cin >> vyska_kmene;
    cout << endl;

    // int n_min = min(1, sirka_stromu);
    // max(n_min);

    for (int v = vyska_stromu; v > 0; v--) {
        string mezery = "";

        for (int m = v; m > 0; m--) {
            mezery += " ";
        }

        string listy = "*";
        for (int l = 0; l < sirka_stromu - v; l++ ) {
            listy += "**";
        }

        cout << mezery << listy << mezery << "\n";
    }

    for (int v = vyska_kmene; v > 0; v--) {
        string mezery = "";

        if (sirka_kmene == 1) {
            mezery += " ";
        }

        for (int m = sirka_stromu - floor(sirka_kmene / 2); m > 0; m--) {
            mezery += " ";
        }

        string kmen = "";
        for (int l = 0; l < sirka_kmene; l++ ) {
            kmen += "|";
        }

        cout << mezery << kmen << "\n";
    }
    
    

    //     *
    //    ***
    //   *****
    //  *******
    // ********* 
    //     |
    return  0;
}