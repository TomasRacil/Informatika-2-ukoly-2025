#include "mag.h"
using namespace std;

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila) {
    // TODO: Inicializujte atribut _mana
    _mana = mana;
}

void Mag::utok(Postava& cil) {
    // TODO: Implementujte maguv útok
    // 1. Pokud má mág dostatek many (>= 10):
    //    - Vypište "Sesila FIREBALL"
    //    - Způsobte poškození: _sila * 2
    //    - Odečtěte 10 many
    if (_mana >= 10)
    {
        cout << _jmeno << "sessílá FIREBALL" << endl;
        double damage = _sila * 2;
        _mana -= 10;
        cil.prijmiUtok(damage);
    }
    // 2. Pokud nemá dostatek many:
    //    - Vypište "Dosla mana, uderi holi"
    //    - Způsobte poškození: _sila * 0.5
    //    - Přičtěte 5 many (regenerace)
    else
    {
        cout << _jmeno << "Došla mana, udeří holí" << endl;
        double damage = _sila * 0.5;
        _mana += 5;
        cil.prijmiUtok(damage);
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}