#include "mag.h"

using namespace std;

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) {}

void Mag::utok(Postava& cil) {
        if (_mana >= 10.0) {
        cout << _jmeno << " seslal FIREBALL na " << std::endl;
        double dmg = _sila * 2.0;
        cil.prijmiUtok(dmg);
        _mana -= 10.0;
    } else {
        cout << _jmeno << " - dosla mana, udeři holi!" << std::endl;
        double dmg = _sila * 0.5;
        cil.prijmiUtok(dmg);
        _mana += 5.0; 
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}