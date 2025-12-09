#include "mag.h"
#include <iostream>
#include <algorithm>

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) {
}

void Mag::utok(Postava& cil) {
    // pokud má >=10 many, silny fireball (2x), jinak slabší úder holí (0.5x) a mana se regeneruje
    if (_mana >= 10.0) {
        std::cout << _jmeno << " seslal FIREBALL na " << cil.getJmeno() << "!" << std::endl;
        double dmg = _sila * 2.0;
        cil.prijmiUtok(dmg);
        _mana -= 10.0;
        if (_mana < 0.0) _mana = 0.0;
    } else {
        std::cout << _jmeno << " - dosla mana, udeři holi!" << std::endl;
        double dmg = _sila * 0.5;
        cil.prijmiUtok(dmg);
        _mana += 5.0; // regenerace
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " / " << _maxZivoty
              << " | DMG: " << _sila << " | Mana: " << _mana << std::endl;
}
