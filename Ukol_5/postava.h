#pragma once
#include <string>
#include <iostream>

// Zakladni trida
class Postava {
protected:
    std::string _jmeno;
    double _zivoty;
    double _sila;
    double _maxZivoty;

public:
    Postava(const std::string& jmeno, double zivoty, double sila);
    
    virtual ~Postava() = default;

    std::string getJmeno() const;
    double getZivoty() const;
    double getMaxZivoty() const;
    bool jeZiva() const;

    virtual void utok(Postava& cil);
    virtual void prijmiUtok(double poskozeni);
    virtual void vypisInfo() const;
};