#include "valecnik.h"

Valecnik::Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila), _brneni(brneni) { // Volání konstruktoru předka
    // TODO: Inicializujte atribut _brneni
}

void Valecnik::utok(Postava& cil) {
    // TODO: Implementujte útok válečníka
    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()
    double utocnaSila=_sila;
    if(_zivoty < 0.3 * _maxZivoty)
    {
        std::cout << _jmeno << " je v zurivem modu a utoci vetsi silou!" << std::endl;
        utocnaSila *=1.5;
    }
        
    std::cout << _jmeno << "utoci na " << cil.getJmeno() << "se silou " << utocnaSila << std::endl;
    cil.prijmiUtok(utocnaSila);


}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    // 3. Vypište informaci o blokování.
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.
    std::cout << _jmeno << " blokuje " << _brneni << "poskozeni" << std::endl;
    double snizenePoskozeni = poskozeni - _brneni;
    if(snizenePoskozeni<0)
    {
        snizenePoskozeni=0;
    }
    Postava::prijmiUtok(snizenePoskozeni);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}