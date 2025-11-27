#include <iostream>
#include <vector>
using namespace std;

void den(vector<int>& ryby) {
    size_t n = ryby.size();           // počet ryb na začátku dne
    for (size_t i = 0; i < n; ++i) {  // projdeme jen „staré“ ryby
        if (ryby[i] == 0) {
            ryby[i] = 6;
            ryby.push_back(8);        // nová ryba (ta se dnes už NEZPRACUJE)
        } else {
            --ryby[i];
        }
    }
}

int main() {
    vector<int> ryby = {3,4,3,1,2};

    for (int d = 0; d < 5; ++d) {   // kolik dní simulovat
        den(ryby);
        // případně lehký denní report:
        // cout << "Den " << d+1 << ", pocet: " << ryby.size() << "\n";
    }

    // závěrečný výstup:
    cout << "Pocet ryb: " << ryby.size() << "\n";
    // Pokud chceš vypsat všechny:
    // for (int r : ryby) cout << r << ' ';
    // cout << '\n';
}
