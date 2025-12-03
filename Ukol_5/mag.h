#pragma once
#include "postava.h"

class Mag : public Postava {
private:
    double _mana;

public:
    Mag(const std::string& jmeno, double zivoty, double sila, double mana);

    void utok(Postava& cil) override;
    void vypisInfo() const override;
};
