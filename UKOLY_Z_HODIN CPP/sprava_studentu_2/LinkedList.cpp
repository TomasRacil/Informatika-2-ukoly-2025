#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <sstream>

LinkedList::LinkedList(const std::string &filename)
{
    this->filename = filename;
    std::ifstream soubor(filename);
    std::string radek;
    pHead = new Node *;
    *pHead = nullptr;

    if (!soubor.is_open())
    {
        std::cout << "soubor se nepodařilo otevřít" << std::endl;
    }
    else
    {
        while (getline(soubor, radek))
        {
            if (radek.find("#") != 0 || radek.empty())
            {
                pridejStudentaNaKonec(Student(radek));
            }
        }
    }
    soubor.close();
}
void LinkedList::vypisSeznam()
{
    Node *current = *pHead;
    while (current != nullptr)
    {
        current->vypis_node();
        current = current->get_next();
    }
}

void LinkedList::pridejStudentaNaKonec(Student new_Student)
{
    Node *newNode = new Node(new_Student);
    if (*pHead == nullptr)
    {
        *pHead = newNode;
    }
    else
    {
        Node *last = *pHead;

        while (last->get_next() != nullptr)
        {
            last = last->get_next();
        }

        last->set_next(newNode);
    }
}
// void setridSeznamPodlePrumeru()
//     {
//         for (Node *i = *pHead; i != nullptr; i = i->get_next())
//         {
//             Node *minNode = i;
//             for (Node *j = i->get_next(); j != nullptr; j = j->get_next())
//             {
//                 if (j->get_student().prumer < minNode->get_student().prumer)
//                 {
//                     minNode = j;
//                 }
//             }
//             if (minNode != i)
//             {
//                 // swap(i->get_student(), minNode->get_student()); TODO
//             }
//         }
//     }

LinkedList::~LinkedList()
{
    ulozStudentyDoSouboru();
    Node *current = *pHead;
    while (current != nullptr)
    {
        Node *next = current->get_next();
        delete current;
        current = next;
    }
    *pHead = nullptr;
}

void LinkedList::ulozStudentyDoSouboru()
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Chyba pri otevirani souboru" << filename << std::endl;
        return;
    }
    Node *current = *pHead;
    while (current != nullptr)
    {
        file << *current<< std::endl;
        current = current->get_next();
    }
    file.close();
}

std::ostream& operator<<(std::ostream& out, LinkedList& m)
{
	Node *current = *m.pHead;
    while (current != nullptr)
    {
        // out<<"Adresa prvku: "<<current<<", "<<*current;
        out<<*current;
        current = current->get_next();
    }
	return out;
}