#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka
    // TODO: Inicializujte atribut _brneni
    _brneni = brneni;
}

void Valecnik::utok(Postava& cil) {
    // TODO: Implementujte útok válečníka
    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()

    double poskozeni = _sila;

if (_zivoty < 0.3 * _maxZivoty) {
    std::cout << "[Valecnik] " << _jmeno << " upada do zurivosti!" << std::endl;
    poskozeni *= 1.5;
}

std::cout << "[Valecnik] " << _jmeno << " utoci na " << cil.getJmeno()
          << " silou " << poskozeni << std::endl;

cil.prijmiUtok(poskozeni);

}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    // 3. Vypište informaci o blokování.
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.

    double efektivni = poskozeni - _brneni;
    if (efektivni < 0)
        efektivni = 0;

    std::cout << "[Valecnik] " << _jmeno << " blokuje " << _brneni
              << " dmg, utrpi " << efektivni << std::endl;

    Postava::prijmiUtok(efektivni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}
