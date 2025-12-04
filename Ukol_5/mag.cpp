#include "mag.h"

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila) {
    _mana = mana;
}

void Mag::utok(Postava& cil) {
if (_mana >= 10){
    std::cout << getJmeno() << "Sesila FIREBALL" << endl;
    cil.prijmiUtok(2 * _sila);
    _mana -= 10;
    }
else{ 
        std::cout << getJmeno() << "Dosla mana, uderi holi" << endl;
        cil.prijmiUtok(_sila * 0.5);
        _mana += 5;
    }
    
}
    // TODO: Implementujte maguv útok
    // 1. Pokud má mág dostatek many (>= 10):
    //    - Vypište "Sesila FIREBALL"
    //    - Způsobte poškození: _sila * 2
    //    - Odečtěte 10 many
    // 2. Pokud nemá d ostatek many:
    //    - Vypište "Dosla mana, uderi holi"
    //    - Způsobte poškození: _sila * 0.5
    //    - Přičtěte 5 many (regenerace)

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}
