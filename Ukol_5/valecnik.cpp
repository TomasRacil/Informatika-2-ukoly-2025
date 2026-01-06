#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) { // Volání konstruktoru předka
    // Inicializace brnění proběhla v inicializačním seznamu výše
}

void Valecnik::utok(Postava& cil) {
    // TODO: Implementujte útok válečníka
    
    // Spočítáme hranici pro Berserk (30 % z maximálních životů)
    // Používáme _maxZivoty, které jsou definované v předkovi Postava
    double berserkHranice = _maxZivoty * 0.3;

    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů
    if (_zivoty < berserkHranice) {
        // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
        std::cout << "[Valecnik] " << _jmeno << " ZURI! (Berserk mode aktivovan)" << std::endl;
        cil.prijmiUtok(_sila * 1.5);
    } else {
        // 3. Pokud ne, útočte normální silou.
        std::cout << "[Valecnik] " << _jmeno << " utoci mecem." << std::endl;
        cil.prijmiUtok(_sila);
    }
}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    double redukovanePoskozeni = poskozeni - _brneni;

    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    if (redukovanePoskozeni < 0) {
        redukovanePoskozeni = 0;
    }

    // 3. Vypište informaci o blokování.
    std::cout << "[Valecnik] " << _jmeno << " blokuje utok (Brneni: " 
              << _brneni << ", Prijato: " << redukovanePoskozeni << ")" << std::endl;

    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.
    Postava::prijmiUtok(redukovanePoskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}