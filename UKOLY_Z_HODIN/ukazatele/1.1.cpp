#include <iostream>

/**
 * @brief Najde adresy nejmenšího a největšího prvku v poli.
 * * @param pPrvniPrvek Ukazatel na první prvek pole, které prohledáváme.
 * @param pocetPrvku Počet prvků v poli.
 * @param vystup_adresa_pro_nejvetsi Výstupní parametr: Adresa ukazatele (int**), 
 * kam funkce uloží adresu nalezeného maxima.
 * @param vystup_adresa_pro_nejmensi Výstupní parametr: Adresa ukazatele (int**), 
 * kam funkce uloží adresu nalezeného minima.
 */
void najdiAdresyMinMax(int* pAktualniPrvek, int pocetPrvku, 
    int** vystup_adresa_pro_nejvetsi, int** vystup_adresa_pro_nejmensi) {
    
    // Používáme 'p' prefix pro ukazatele
    int* pAdresaZaKoncem = pAktualniPrvek + pocetPrvku;

    if (pocetPrvku == 0) {
        *vystup_adresa_pro_nejvetsi = nullptr;
        *vystup_adresa_pro_nejmensi = nullptr;
        return;
    }

    // Inicializace
    *vystup_adresa_pro_nejvetsi = pAktualniPrvek;
    *vystup_adresa_pro_nejmensi = pAktualniPrvek;

    // Procházení pole
    while (pAktualniPrvek != pAdresaZaKoncem) {
        
        // *pAktualniPrvek              -> HODNOTA aktuálního prvku
        // **vystup_adresa_pro_nejmensi -> HODNOTA dosavadního minima
        
        if (**vystup_adresa_pro_nejmensi > *pAktualniPrvek) {
            // Našli jsme nové minimum.
            // Změníme ukazatel v 'main' (přes jeho adresu), aby ukazoval sem.
            *vystup_adresa_pro_nejmensi = pAktualniPrvek;
        }

        if (**vystup_adresa_pro_nejvetsi < *pAktualniPrvek) {
            // Našli jsme nové maximum.
            *vystup_adresa_pro_nejvetsi = pAktualniPrvek;
        }

        // Posun na další prvek
        pAktualniPrvek++;
    }
}

int main() {
    int dataPole[10] = {9, 4, 6, 27, 9, 2, 3, 7, 5, 8};

    //'p' prefix označuje ukazatel
    int* p_nejmensi_prvek = nullptr;
    int* p_nejvetsi_prvek = nullptr;

    // Předáváme adresu ukazatele p_nejmensi_prvek (typ int**)
    // a adresu ukazatele p_nejvetsi_prvek (typ int**)
    najdiAdresyMinMax(dataPole, 10, &p_nejvetsi_prvek, &p_nejmensi_prvek);

    std::cout << "\n--- Vysledek ---" << std::endl;
    if (p_nejmensi_prvek != nullptr && p_nejvetsi_prvek != nullptr) {
        std::cout << "Nejmensi hodnota: " << *p_nejmensi_prvek 
                  << " (nalezena na adrese: " << p_nejmensi_prvek << ")" << std::endl;
        
        std::cout << "Nejvetsi hodnota: " << *p_nejvetsi_prvek 
                  << " (nalezena na adrese: " << p_nejvetsi_prvek << ")" << std::endl;
    } else {
        std::cout << "Pole bylo prazdne, min/max nebylo nalezeno." << std::endl;
    }

    return 0;
}