#include "mag.h"

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) { // Init many v seznamu
    // TODO: Inicializujte atribut _mana
    // (Provedeno v inicializačním seznamu výše: , _mana(mana))
}

void Mag::utok(Postava& cil) {
    // TODO: Implementujte maguv útok
    // 1. Pokud má mág dostatek many (>= 10):
    if (_mana >= 10) {
        // - Vypište "Sesila FIREBALL"
        std::cout << "[Mag] " << _jmeno << " sesila FIREBALL!" << std::endl;
        
        // - Způsobte poškození: _sila * 2
        cil.prijmiUtok(_sila * 2);
        
        // - Odečtěte 10 many
        _mana -= 10;
    } 
    // 2. Pokud nemá dostatek many:
    else {
        // - Vypište "Dosla mana, uderi holi"
        std::cout << "[Mag] " << _jmeno << " dosla mana, uderi holi." << std::endl;
        
        // - Způsobte poškození: _sila * 0.5
        cil.prijmiUtok(_sila * 0.5);
        
        // - Přičtěte 5 many (regenerace)
        _mana += 5;
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}