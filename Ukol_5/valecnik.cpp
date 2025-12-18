#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) { 
    
}

void Valecnik::utok(Postava& cil) {
    double aktualniSila = _sila;
    if (_zivoty < 0.3 * _maxZivoty){
        std::cout << _jmeno << " je v berserk modu " <<std::endl;
        aktualniSila *= 1.5;
    }
    std::cout << _jmeno << " utoci na " << cil.getJmeno() << " se silou " << aktualniSila << std::endl;
    cil.prijmiUtok(aktualniSila);
}

void Valecnik::prijmiUtok(double poskozeni) {
    std::cout << _jmeno << " blokuje utok s brnenim " << _brneni << std::endl;
    double snizenePoskozeni = poskozeni - _brneni;
    if (snizenePoskozeni < 0){
        snizenePoskozeni = 0;
    }
    Postava::prijmiUtok(snizenePoskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}