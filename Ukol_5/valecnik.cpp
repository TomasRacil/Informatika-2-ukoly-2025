#include "valecnik.h"

using namespace std;

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) { 
}

void Valecnik::utok(Postava& cil) {
    double hpRatio = (_maxZivoty > 0.0) ? (_zivoty / _maxZivoty) : 0.0;
    if (hpRatio < 0.30) {
        cout << _jmeno << " je v berserk modu a útočí silou " << (_sila * 1.5) << "!" << endl;
        cil.prijmiUtok(_sila * 1.5);
    } else {
        cout << _jmeno << " udeří normálně silou " << _sila << "." << endl;
        cil.prijmiUtok(_sila);
    }
}

void Valecnik::prijmiUtok(double poskozeni) {
    if (poskozeni < 0.0) poskozeni = 0.0;
    double effective = poskozeni - _brneni;
    if (effective <= 0.0) {
        effective = 0.0;
        cout << _jmeno << " zablokoval utok (armor " << _brneni << ")!" << endl;
    } else {
        cout << _jmeno << " blokoval " << _brneni << " z damage." << endl;
    }
    Postava::prijmiUtok(effective);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}