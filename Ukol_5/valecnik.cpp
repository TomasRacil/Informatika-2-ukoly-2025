#include "valecnik.h"
#include <iostream>
#include <algorithm>

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) {
}

void Valecnik::utok(Postava& cil) {
    // jednoduchý berserk: pokud má méně než 30% max HP, útočí silněji
    double hpRatio = (_maxZivoty > 0.0) ? (_zivoty / _maxZivoty) : 0.0;
    if (hpRatio < 0.30) {
        std::cout << _jmeno << " je v berserk modu a útočí silou " << (_sila * 1.5) << "!" << std::endl;
        cil.prijmiUtok(_sila * 1.5);
    } else {
        std::cout << _jmeno << " udeří normálně silou " << _sila << "." << std::endl;
        cil.prijmiUtok(_sila);
    }
}

void Valecnik::prijmiUtok(double poskozeni) {
    // snížení poškození o armor
    if (poskozeni < 0.0) poskozeni = 0.0;
    double effective = poskozeni - _brneni;
    if (effective <= 0.0) {
        effective = 0.0;
        std::cout << _jmeno << " zablokoval utok (armor " << _brneni << ")!" << std::endl;
    } else {
        std::cout << _jmeno << " blokoval " << _brneni << " z damage." << std::endl;
    }
    Postava::prijmiUtok(effective);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " / " << _maxZivoty
              << " | DMG: " << _sila << " | Armor: " << _brneni << std::endl;
}
