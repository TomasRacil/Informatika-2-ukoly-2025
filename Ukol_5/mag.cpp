#include "mag.h"

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila) {
    _mana = mana;
}

void Mag::utok(Postava& cil) {
    if (jeZiva()) {
        if (_mana >= 10) {
            std::cout << this->getJmeno() << " sesila FIREBALL!" << std::endl;
            cil.prijmiUtok(this->_sila * 2);
            _mana -= 10;
        } else {
            std::cout << this->getJmeno() << " dosla mana, uderi holi!" << std::endl;
            cil.prijmiUtok(this->_sila * 0.5);
            _mana += 5;
        }
    }

}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}