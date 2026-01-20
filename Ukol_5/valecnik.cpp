#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka

    _brneni = brneni;
}

void Valecnik::utok(Postava& cil) {
    if (jeZiva()) {
        if (_zivoty < 0.3 * _maxZivoty) {
            std::cout << this->getJmeno() << " je v zurivem modu a utoci silou " << this->_sila * 1.5 << "!" << std::endl;
            cil.prijmiUtok(this->_sila * 1.5);
        } else {
            std::cout << this->getJmeno() << " utoci na " << cil.getJmeno() << " silou " << this->_sila << std::endl;
            cil.prijmiUtok(this->_sila);
        }
    }
   
}

void Valecnik::prijmiUtok(double poskozeni) {
    double snizenePoskozeni = poskozeni - _brneni;
    if (snizenePoskozeni < 0) {
        snizenePoskozeni = 0;
    }
    std::cout << this->getJmeno() << " blokuje " << _brneni << " poskozeni brnenim!" << std::endl;
    Postava::prijmiUtok(snizenePoskozeni);
    
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}