#include "postava.h"
#include <iostream> // Potřeba pro cout

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
    // TODO: Vraťte true, pokud jsou životy > 0
    return _zivoty > 0;
}

void Postava::utok(Postava& cil) {
    // TODO: Implementujte základní útok
    std::cout << "[Postava] " << _jmeno << " utoci na " << cil.getJmeno() 
              << " silou " << _sila << std::endl;
    
    cil.prijmiUtok(this->_sila);
}

void Postava::prijmiUtok(double poskozeni) {
    // TODO: Implementujte přijetí poškození
    
    // 1. Ochrana proti zápornému poškození (léčení útokem nedává smysl)
    if (poskozeni < 0) {
        poskozeni = 0;
    }

    // 2. Odečtení poškození
    _zivoty -= poskozeni;

    // 3. Ořezání na 0 (nemůžeme mít -10 životů)
    if (_zivoty < 0) {
        _zivoty = 0;
    }
}

void Postava::vypisInfo() const {
    std::cout << "[Postava] " << _jmeno << " | HP: " << _zivoty << " | DMG: " << _sila << std::endl;
}