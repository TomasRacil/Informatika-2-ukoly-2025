#include <iostream> //cout, cin
#include <string> //string
#include <sstream> //stringstream, rozdělení řádku podle čárek
#include <fstream> //fstream, práce se soubory
#include <stdexcept> //výjimky
#include <iomanip>  //formátovaání průměru na více deseetinných míst
#include <cctype> // ořezávání mezer

using std::cout; //kratší zápis std::cout -> cout
using std::string; //kratší zápis stringu
using std::cerr; //kratší zápis std::cerr -> cerr
using std::size_t; //kratší zápis size_t

//====Datové struktury====

struct Student {
    int id{};
    string name{};
    double prumer{};
};

struct Uzel {
    Student data;
    Uzel* dalsi = nullptr;
};

//====Výpis studenta====
std::ostream& operator<<(std::ostream& os, const Student& student) {    
    os << "ID: "; 
    os << student.id;
    os << "|";

    os << " Jméno: ";
    os << student.name;
    os << "|";

    os << " Průměr: ";
    os << std::fixed;
    os << std::setprecision(2);
    os << student.prumer;

    return os;
}

//====Parsování studenta ze stringu====

Student parsujRadek(const string& radek) {
    if (radek.empty()) {
        throw std::invalid_argument("Prázdný řádek");
    }


}


