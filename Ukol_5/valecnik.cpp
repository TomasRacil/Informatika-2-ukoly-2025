#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) {}

void Valecnik::utok(Postava& cil) {
    double dmg = _sila;
    if (_zivoty < _maxZivoty * 0.3) { // berserk if below 30% HP
        dmg *= 1.5;
        std::cout << _jmeno << " je zuřivý a útočí silou " << dmg << "!" << std::endl;
    }
    else {
        std::cout << _jmeno << " útočí silou " << dmg << std::endl;
    }
    cil.prijmiUtok(dmg);
}

void Valecnik::prijmiUtok(double poskozeni) {
    double actualDamage = poskozeni - _brneni;
    if (actualDamage < 0) actualDamage = 0;
    std::cout << _jmeno << " blokuje " << _brneni << " poškození, přijímá " << actualDamage << std::endl;
    Postava::prijmiUtok(actualDamage);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}

