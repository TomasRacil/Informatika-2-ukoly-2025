#include "Student.h"
#include <sstream>
#include <iomanip>

Student::Student(){
    
}

Student::Student(int id, std::string name, double prumer)
{
    this->id = id;
    this->name = name;
    this->prumer = prumer;
}

Student::Student(std::string radek){
    std::stringstream ss(radek);
    std::string idStr, nameStr, prumerStr;

    std::getline(ss, idStr, ',');
    std::getline(ss, nameStr, ',');
    std::getline(ss, prumerStr, ',');

    id = stoi(idStr);
    name = nameStr;
    prumer = stod(prumerStr);
}

std::ostream& operator<<(std::ostream& out, Student& m){
    out << m.id << ", " << m.name << ", " << m.prumer;
    return out;
}