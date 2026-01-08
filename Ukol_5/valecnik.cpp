#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka

    _brneni = brneni;
}

void Valecnik::utok(Postava& cil) {
    if (jeZiva()) {
        if (_zivoty < 0.3 * _maxZivoty) {
            std::cout << this->getJmeno() << " je v zurivem modu a utoci silou " << this->_sila * 1.5 << "!" << std::endl;
            cil.prijmiUtok(this->_sila * 1.5);
        } else {
            std::cout << this->getJmeno() << " utoci na " << cil.getJmeno() << " silou " << this->_sila << std::endl;
            cil.prijmiUtok(this->_sila);
        }
    }
   
}

void Valecnik::prijmiUtok(double poskozeni) {
    double snizenePoskozeni = poskozeni - _brneni;
    if (snizenePoskozeni < 0) {
        snizenePoskozeni = 0;
    }
    std::cout << this->getJmeno() << " blokuje " << _brneni << " poskozeni brnenim!" << std::endl;
    Postava::prijmiUtok(snizenePoskozeni);
    

    // TODO: Inicializujte atribut _brneni
}

void Valecnik::utok(Postava& cil) {
    // TODO: Implementujte útok válečníka
    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()
}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    // 3. Vypište informaci o blokování.
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.

}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}