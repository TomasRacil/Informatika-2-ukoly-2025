
#include <iostream>

#include <vector>

#include <algorithm>


using namespace std;


int main() {

    int pocetVetvi = 0;

    
    cout << "Zadej pocet vetvi (pocet radku koruny stromu): ";
   
    cin >> pocetVetvi;

    
    vector<int> sirkyVetvi;
    
    sirkyVetvi.reserve(pocetVetvi);

    
    for (int i = 0; i < pocetVetvi; ++i) {
        
        int s = 0;
        
        cout << "Zadej sirku " << (i + 1) << ". vetve (doporučeno liche cislo, napr. 3, 5, 7...): ";
       

        
        if (s < 1) {
            s = 1;
        }
        
        if (s % 2 == 0) {
            ++s;
        }
        
        sirkyVetvi.push_back(s);
    }
    int sirkaKmene = 0;
    int vyskaKmene = 0;

  
    cout << "Zadej sirku kmene (doporučeno male liche cislo, napr. 1 nebo 3): ";
    
    cin >> sirkaKmene;

    
    if (sirkaKmene < 1) {
        sirkaKmene = 1;
    }
    
    if (sirkaKmene % 2 == 0) {
        ++sirkaKmene;
    }

    
    cout << "Zadej vysku kmene (kolik radku): ";
    
    cin >> vyskaKmene;
    int maxSirkaKoruny = 1; 
    if (!sirkyVetvi.empty()) {
        maxSirkaKoruny = *max_element(sirkyVetvi.begin(), sirkyVetvi.end());
    }
    
    int celkovaSirka = max(maxSirkaKoruny, sirkaKmene);

    
    cout << "\n--- Vykresluji strom ---\n";

    
    for (int s : sirkyVetvi) {
        
        int mezery = (celkovaSirka - s) / 2;
        
        for (int i = 0; i < mezery; ++i) {
            cout << ' ';
        }
        
        for (int i = 0; i < s; ++i) {
            cout << '*';
        }
        
        cout << '\n';
    }

    
    for (int r = 0; r < vyskaKmene; ++r) {
        
        int mezery = (celkovaSirka - sirkaKmene) / 2;
        
        for (int i = 0; i < mezery; ++i) {
            cout << ' ';
        }
        
        for (int i = 0; i < sirkaKmene; ++i) {
            cout << '#';
        }
        
        cout << '\n';
    }

    cout << "--- Hotovo ---\n";


    return 0;
}

