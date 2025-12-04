#include "valecnik.h"
using namespace std;
Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka
    _brneni = brneni;
}

void Valecnik::utok(Postava& cil) {
    if(getZivoty() < 0.3 * getMaxZivoty()){
    cout << getJmeno() << "je Berserk dává větší damage" << endl;
    cil.prijmiUtok(1.5 * _sila);
    }else{ cil.prijmiUtok(_sila);
    }
    // TODO: Implementujte útok válečníka
        // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()
}

void Valecnik::prijmiUtok(double poskozeni) {
    poskozeni -= _brneni;
     if(poskozeni < 0){
    poskozeni = 0;
    };
    if (poskozeni = 0){
    cout << getJmeno() << "zablokoval utok" << endl;
    }
Postava::prijmiUtok(poskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}