#include "valecnik.h"
using namespace std;

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila) { // Volání konstruktoru předka
    // TODO: Inicializujte atribut _brneni
    _brneni = brneni;

}

void Valecnik::utok(Postava& cil) {
    // TODO: Implementujte útok válečníka
    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()
    if(_zivoty < 0.3 * _maxZivoty)
    {
        cout << this -> _jmeno << "je v Berserk módu (utok 1,5x)!" << endl;
        double damage = _sila * 1.5;
        cil.prijmiUtok(damage);
    }
    else
    {
        double damage = _sila;
        cil.prijmiUtok(damage);
    }

}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    double snizenePoskozeni = poskozeni - _brneni;
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    if(snizenePoskozeni < 0)
    {
        snizenePoskozeni = 0;
    }
    // 3. Vypište informaci o blokování.
    cout << this -> _jmeno << "blokuje" << (_brneni < poskozeni ? _brneni : poskozeni) << "poškození." << endl;
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.
    Postava::prijmiUtok(snizenePoskozeni);

}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}