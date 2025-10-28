#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ---------------------------
// Structs
// ---------------------------

struct Student
{
    int id;
    string jmeno;
    double prumer;
};

struct Uzel
{
    Student data;
    Uzel* next;
};

// ---------------------------
// Functions
// ---------------------------

// Allocates and reads entire file into stringstream
stringstream open_file(const string& file_name)
{
    ifstream soubor(file_name);
    if (!soubor.is_open())
    {
        cerr << "File " << file_name << " could not be opened!" << endl;
        return stringstream();
    }

    stringstream content;
    content << soubor.rdbuf();
    return content;
}

// Parses a line "id jmeno prumer" into a Student
Student parsujRadek(const string& radek)
{
    Student new_student;
    stringstream ss(radek);
    ss >> new_student.id >> new_student.jmeno >> new_student.prumer;
    return new_student;
}

// Prints all students in linked list
void printStudents(Uzel* head)
{
    Uzel* current = head;
    while (current)
    {
        cout << current->data.id << " "
             << current->data.jmeno << " "
             << current->data.prumer << endl;
        current = current->next;
    }
}

// Frees linked list memory
void freeList(Uzel* head)
{
    while (head)
    {
        Uzel* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ---------------------------
// Main
// ---------------------------

int main()
{
    stringstream soubor_content_ss = open_file("studenti.txt");
    string line;

    Uzel* head = nullptr; // start of linked list

    while (getline(soubor_content_ss, line))
    {
        if (line.empty()) continue; // skip empty lines
        Student s = parsujRadek(line);

        // Add to linked list (insert at head)
        Uzel* node = new Uzel{ s, head };
        head = node;
    }

    cout << "All students:" << endl;
    printStudents(head);

    // Free memory
    freeList(head);

    return 0;
}
