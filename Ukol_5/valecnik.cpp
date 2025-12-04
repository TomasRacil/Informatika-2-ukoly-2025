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
    double current = getZivoty();
    double maxhp = getMaxZivoty();
    double dmg = _sila;
    if (maxhp > 0.0 && current < 0.3 * maxhp) {
        std::cout << _jmeno << " je v zuřivosti! (BERSERK)" << std::endl;
        dmg = _sila * 1.5;
    }
    std::cout << _jmeno << " utoci na " << cil.getJmeno() << " silou " << dmg << std::endl;
    cil.prijmiUtok(dmg);
}

void Valecnik::prijmiUtok(double poskozeni) {
    // TODO: Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    // 3. Vypište informaci o blokování.
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.
    double adjusted = poskozeni - _brneni;
    if (adjusted < 0.0) adjusted = 0.0;
    std::cout << _jmeno << " blokuje " << _brneni << " poškození:" << adjusted << std::endl;
    Postava::prijmiUtok(adjusted);
}

void Valecnik::vypisInfo() const {
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}