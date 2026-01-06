#include "mag.h"
#include <iostream>

Mag::Mag(const std::string& jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila), _mana(mana) {
    // TODO: Inicializujte atribut _mana - HOTOVO v inicializačním seznamu výše
}

void Mag::utok(Postava& cil) {
    // TODO: Implementujte maguv útok
    
    // 1. Kontrola many
    if (_mana >= 10) {
        std::cout << "[Magie] " << _jmeno << " sesila FIREBALL na " << cil.getJmeno() << "!" << std::endl;
        
        // Způsobte poškození: _sila * 2
        cil.prijmiUtok(_sila * 2);
        
        // Odečtěte manu
        _mana -= 10;
    } 
    // 2. Nedostatek many
    else {
        std::cout << "[Magie] " << _jmeno << " - Dosla mana! Uderi jen holi." << std::endl;
        
        // Slabý útok
        cil.prijmiUtok(_sila * 0.5);
        
        // Regenerace
        _mana += 5;
        std::cout << "   (Mana dobita na " << _mana << ")" << std::endl;
    }
}

void Mag::vypisInfo() const {
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}