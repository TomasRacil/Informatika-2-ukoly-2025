#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;

struct Student
{
    int id;
    string jmeno;
    double prumer;
};

struct Uzel
{
    struct Student;
    struct Uzel *next;
};

void parsujRadek(string& radek)
{
    Student new_student;
    string radek;
    

    // return {"student"};
}

stringstream open_file(string file_name)
{
    ifstream soubor(file_name);

    if (!soubor || !soubor.is_open())
    {
        return stringstream();
    }

    stringstream content;

    content << soubor.rdbuf();
    soubor.close();

    return content;
}

int main()
{
    stringstream soubor_content_ss = open_file("studenti.txt");

    return 0;
}