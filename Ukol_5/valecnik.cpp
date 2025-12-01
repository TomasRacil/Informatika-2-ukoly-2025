#include "valecnik.h"

using namespace std;

Valecnik::Valecnik(const std::string &jmeno, double zivoty, double sila, double brneni)
    : Postava(jmeno, zivoty, sila)
{ // Volání konstruktoru předka
    _brneni = brneni;
}

void Valecnik::utok(Postava &cil)
{
    // Implementujte útok válečníka
    // 1. Zkontrolujte, zda má válečník méně než 30 % maximálních životů (berserk mode).
    //    (Pozor: v zadání není max_hp, pro zjednodušení předpokládejme, že < 30 HP = berserk)
    // 2. Pokud ano, vypište hlášku o zuřivosti a útočte silou * 1.5
    // 3. Pokud ne, útočte normální silou.
    // Tip: Využijte metodu cil.prijmiUtok()
    double b_poskozeni = _sila * 1.5; // b jako berserk

    if (_zivoty < (0.3 * _maxZivoty))
    {
        cout << "Zurivost" << endl;
        cil.prijmiUtok(b_poskozeni);
    }
    else
    {
        cil.prijmiUtok(_sila);
    }
}

void Valecnik::prijmiUtok(double poskozeni)
{
    // Implementujte obranu válečníka
    // 1. Snižte příchozí poškození o hodnotu _brneni.
    // 2. Pokud je výsledek menší než 0, nastavte ho na 0.
    // 3. Vypište informaci o blokování.
    // 4. Zavolejte metodu předka Postava::prijmiUtok() se sníženým poškozením.
    double blokovane = poskozeni - _brneni;
    if (blokovane < 0)
    {
        blokovane = 0;
    }
    cout << "Utok blokovan" << endl;
    Postava::prijmiUtok(blokovane);
}

void Valecnik::vypisInfo() const
{
    std::cout << "[Valecnik] " << _jmeno << " | HP: " << _zivoty << " | Armor: " << _brneni << std::endl;
}