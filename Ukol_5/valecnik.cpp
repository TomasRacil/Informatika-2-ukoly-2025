#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) { 
}

void Valecnik::utok(Postava& cil) {
    double dmg = _sila;

    if (_zivoty < 30) {
        std::cout << _jmeno << " upada do ZURENÍ (BERSERK)!" << std::endl;
        dmg *= 1.5;
    }

    std::cout << _jmeno << " utoci mecem silou " << dmg << std::endl;

    cil.prijmiUtok(dmg);
}

void Valecnik::prijmiUtok(double poskozeni) {
   double realPoskozeni = poskozeni - _brneni;

    if (realPoskozeni < 0)
        realPoskozeni = 0;

    std::cout << _jmeno << " blokuje " << _brneni
              << " poskozeni brnenim. Utrpene poskozeni: "
              << realPoskozeni << std::endl;

    Postava::prijmiUtok(realPoskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}
