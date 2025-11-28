#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka
    // TODO: Inicializujte atribut _brneni
    this->_brneni = brneni;
    double _maxZivoty = zivoty;
}

void Valecnik::utok(Postava& cil) {
    // TODO: Implementujte útok válečníka
    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()

    if (_zivoty < _maxZivoty * 0.3) {
        std::cout << "Rage" << std::endl;
        cil.prijmiUtok(_sila * 1.5);
    }
    else {
        cil.prijmiUtok(_sila);
    }
}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    // 3. Vypište informaci o blokování.
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.

    poskozeni -= _brneni;
    if (poskozeni < 0) {
        poskozeni = 0;
    }
    std::cout << "Poskozeni blokovano!" << std::endl;
    Postava::prijmiUtok(poskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}