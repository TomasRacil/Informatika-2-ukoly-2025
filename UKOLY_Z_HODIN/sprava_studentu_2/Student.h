#pragma once

#include <string>

struct Student
{
    int id;
    std::string name;
    double prumer;
    Student();
    Student(int id, std::string name, double prumer);
    Student(std::string radek);
};
std::ostream& operator<<(std::ostream& out, Student& m);