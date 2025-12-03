#pragma once
#include "postava.h"

class Valecnik : public Postava {
private:
    double _brneni;

public:
    Valecnik(const std::string& jmeno, double zivoty, double sila, double brneni);

    void utok(Postava& cil) override;
    void prijmiUtok(double poskozeni) override;
    void vypisInfo() const override;
};
