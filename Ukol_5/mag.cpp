#include "mag.h"

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) {
    // TODO: Inicializujte atribut _mana

}

void Mag::utok(Postava& cil) {
    // TODO: Implementujte maguv útok
    // 1. Pokud má mág dostatek many (>= 10):
    //    - Vypište "Sesila FIREBALL"
    //    - Způsobte poškození: _sila * 2
    //    - Odečtěte 10 many
    // 2. Pokud nemá dostatek many:
    //    - Vypište "Dosla mana, uderi holi"
    //    - Způsobte poškození: _sila * 0.5
    //    - Přičtěte 5 many (regenerace)
    if (_mana >= 10.0) {
        std::cout << "Sesila FIREBALL" << std::endl;
        double dmg = _sila * 2.0;
        cil.prijmiUtok(dmg);
        _mana -= 10.0;
        if (_mana < 0.0) _mana = 0.0;

    } else {
        std::cout << "Dosla mana, uderi holi" << std::endl;
        double dmg = _sila * 0.5;
        cil.prijmiUtok(dmg);
        _mana += 5.0;
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}