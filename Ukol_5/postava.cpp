#include "postava.h"

Postava::Postava(const std::string& jmeno, double zivoty, double sila)
    : _jmeno(jmeno), _zivoty(zivoty), _sila(sila), _maxZivoty(zivoty) {
    // Konstruktor je již hotový
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
    return _zivoty > 0;
}

void Postava::utok(Postava& cil) {
    std::cout << _jmeno << " utoci na " << cil.getJmeno() << " silou " << _sila << std::endl;
    cil.prijmiUtok(_sila);
}

void Postava::prijmiUtok(double poskozeni) {
    if (poskozeni < 0) poskozeni = 0;
    _zivoty -= poskozeni;
    if (_zivoty < 0) _zivoty = 0;
}

void Postava::vypisInfo() const {
    std::cout << "[Postava] " << _jmeno << " | HP: " << _zivoty << " | DMG: " << _sila << std::endl;
}