#include "valecnik.h"
#include <iostream>

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) { 
}

void Valecnik::utok(Postava& cil) {
    double aktualniSila = _sila;

    
    double hraniceBerserku = _maxZivoty * 0.3;

    if (_zivoty < hraniceBerserku) {
        std::cout << ">>> " << _jmeno << " propada ZURIVOSTI (Berserk)! <<<" << std::endl;
        aktualniSila = _sila * 1.5;
    }
    

    std::cout << "[Valecnik] " << _jmeno << " drtivy utok na " << cil.getJmeno() << std::endl;
    
    cil.prijmiUtok(aktualniSila);
}

void Valecnik::prijmiUtok(double poskozeni) {
    double redukovanePoskozeni = poskozeni - _brneni;

    if (redukovanePoskozeni < 0) {
        redukovanePoskozeni = 0;
    }

    std::cout << "[Obrana] " << _jmeno << " zblokoval " << _brneni 
              << " poskozeni. Prijima jen " << redukovanePoskozeni << "." << std::endl;

    Postava::prijmiUtok(redukovanePoskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty 
              << " | Armor: " << _brneni << std::endl;
}