#include "mag.h"

using namespace std;

Mag::Mag(const std::string &jmeno, double zivoty, double sila, double mana)
    : Postava(jmeno, zivoty, sila)
{
    _mana = mana;
}

void Mag::utok(Postava &cil)
{
    // 1. Pokud má mág dostatek many (>= 10):
    //    - Vypište "Sesila FIREBALL"
    //    - Způsobte poškození: _sila * 2
    //    - Odečtěte 10 many
    // 2. Pokud nemá dostatek many:
    //    - Vypište "Dosla mana, uderi holi"
    //    - Způsobte poškození: _sila * 0.5
    //    - Přičtěte 5 many (regenerace)
    double poskozeni;
    if (_mana >= 10)
    {
        cout << "Sesila FIREBALL" << endl;
        poskozeni = _sila * 2;
        cil.prijmiUtok(poskozeni);
        _mana -= 10;
    }
    else
    {
        cout << "Dosla mana, uderi holi" << endl;
        poskozeni = _sila * 0.5;
        cil.prijmiUtok(poskozeni);
        _mana += 5;
    }
}

void Mag::vypisInfo() const
{
    std::cout << "[Mag] " << _jmeno << " | HP: " << _zivoty << " | Mana: " << _mana << std::endl;
}