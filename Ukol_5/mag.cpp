#include "mag.h"

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) {}

void Mag::utok(Postava& cil) {
    if (_mana >= 10) {
        std::cout << _jmeno << " sesílá FIREBALL!" << std::endl;
        cil.prijmiUtok(_sila * 2);
        _mana -= 10;
    } else {
        std::cout << _jmeno << " došla mana, udeří holí!" << std::endl;
        cil.prijmiUtok(_sila * 0.5);
        _mana += 5; // regenerate
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}
