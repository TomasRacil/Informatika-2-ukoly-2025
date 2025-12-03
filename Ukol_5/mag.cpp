#include "mag.h"

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) {
}

void Mag::utok(Postava& cil) {
    if (_mana >= 10) {
        std::cout << _jmeno << " sesila FIREBALL!" << std::endl;

        double dmg = _sila * 2;
        cil.prijmiUtok(dmg);

        _mana -= 10;
    }
    else {
        std::cout << _jmeno << " dosla mana, uderi holi!" << std::endl;

        double dmg = _sila * 0.5;
        cil.prijmiUtok(dmg);

        _mana += 5; 
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}
