#include "postava.h"
using namespace std;

Postava::Postava(const std::string& jmeno, double zivoty, double sila)
    : _jmeno(jmeno), _zivoty(zivoty), _sila(sila), _maxZivoty(zivoty) {
    // Konstruktor je již hotový
}

std::string Postava::getJmeno() const {
    return _jmeno;
}

double Postava::getZivoty() const {
    return _zivoty;
}

double Postava::getMaxZivoty() const {
    return _maxZivoty;
}

bool Postava::jeZiva() const {
    if (_zivoty > 0) {
    return true;
    } 
}

void Postava::utok(Postava& cil) {
    cout << _jmeno << "utoci na" << cil.getJmeno() << "silou" << _sila << endl;
    cil.prijmiUtok(this->_sila);
}

void Postava::prijmiUtok(double poskozeni) {
    if(poskozeni < 0){
    poskozeni = 0;
    };
    
    _zivoty -= poskozeni;

    if(_zivoty < 0){
    _zivoty = 0;
    };
    
    // TODO: Implementujte přijetí poškození
    // 1. Pokud je poskozeni < 0, nastavte ho na 0 (obranne mechanismy)
    // 2. Odečtěte poškození od _zivoty
    // 3. Pokud _zivoty klesnou pod 0, nastavte je na 0
}

void Postava::vypisInfo() const {
    std::cout << "[Postava] " << _jmeno << " | HP: " << _zivoty << " | DMG: " << _sila << std::endl;
}