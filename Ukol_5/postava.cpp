#include "postava.h"
#include <iostream>
#include <algorithm>

Postava::Postava(const std::string& jmeno, double zivoty, double sila)
    : _jmeno(jmeno), _zivoty(zivoty), _sila(sila), _maxZivoty(zivoty) {
}

std::string Postava::getJmeno() const {
    return _jmeno;
}

double Postava::getZivoty() const {
    return _zivoty;
}

double Postava::getMaxZivoty() const {
    return _maxZivoty;
}

bool Postava::jeZiva() const {
    return _zivoty > 0.0;
}

void Postava::utok(Postava& cil) {
    // základní útok: způsobí damage rovné _sila
    std::cout << _jmeno << " utoci na " << cil.getJmeno() << " silou " << _sila << std::endl;
    cil.prijmiUtok(this->_sila);
}

void Postava::prijmiUtok(double poskozeni) {
    if (poskozeni < 0.0) poskozeni = 0.0;
    _zivoty -= poskozeni;
    if (_zivoty < 0.0) _zivoty = 0.0;
    std::cout << _jmeno << " prijal " << poskozeni << " damage. (HP: " << _zivoty << "/" << _maxZivoty << ")\n";
}

void Postava::vypisInfo() const {
    std::cout << "[Postava] " << _jmeno << " | HP: " << _zivoty << " / " << _maxZivoty
              << " | DMG: " << _sila << std::endl;
}
