#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka

    _brneni = brneni;
}

void Valecnik::utok(Postava& cil) {

    if (this->getZivoty() <= (this->getMaxZivoty() * 0.3))
    {
        std::cout << "[" << this->getJmeno() << "]" << " zuri, sila 1.5x" << std::endl;
        cil.prijmiUtok(this->_sila * 1.5);
    }
    else
    {
        cil.prijmiUtok(this->_sila);
    }
}

void Valecnik::prijmiUtok(double poskozeni) {

    poskozeni -= this->_brneni;

    if (poskozeni < 0)
    {
        poskozeni = 0;

        std::cout << "[" << this->getJmeno() << "] zablokoval utok!" << std::endl;
    }

    Postava::prijmiUtok(poskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}