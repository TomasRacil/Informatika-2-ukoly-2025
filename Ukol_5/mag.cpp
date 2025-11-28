#include "mag.h"

Mag::Mag(const std::string &jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila)
{
    // TODO: Inicializujte atribut _mana
    _mana = mana;
}

void Mag::utok(Postava &cil)
{
    // TODO: Implementujte maguv útok
    // 1. Pokud má mág dostatek many (>= 10):
    //    - Vypište "Sesila FIREBALL"
    //    - Způsobte poškození: _sila * 2
    //    - Odečtěte 10 many
    // 2. Pokud nemá dostatek many:
    //    - Vypište "Dosla mana, uderi holi"
    //    - Způsobte poškození: _sila * 0.5
    //    - Přičtěte 5 many (regenerace)
    if (_mana >= 10)
    {
        std::cout << _jmeno << " sesila FIREBALL na " << cil.getJmeno() << " silou " << (_sila * 2) << std::endl;
        cil.prijmiUtok(_sila * 2);
        _mana -= 10;
        return;
    }
    std::cout << _jmeno << " dosla mana, uderi holi " << cil.getJmeno() << " silou " << (_sila * 0.5) << std::endl;
    cil.prijmiUtok(_sila * 0.5);
    _mana += 5;
}

void Mag::vypisInfo() const
{
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}