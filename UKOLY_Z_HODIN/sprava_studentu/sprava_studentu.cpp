#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

struct Student
{
    std::string cele_jmeno;
    double prumer;
    int id;
};

struct Node
{
    Student data;
    Node* next;
};

Student parsujRadek(const std::string& radek)
{
    Student student;
    size_t pos1 = radek.find(',');
    size_t pos2 = radek.rfind(',');

    if (pos1 == std::string::npos || pos2 == std::string::npos || pos1 == pos2)
    {
        throw std::invalid_argument("Neplatný formát řádku: " + radek);
    }

    try
    {
        student.id = std::stoi(radek.substr(0, pos1));
        student.cele_jmeno = radek.substr(pos1 + 1, pos2 - pos1 - 1);
        student.prumer = std::stod(radek.substr(pos2 + 1));
    }
    catch (const std::exception& e)
    {
        throw std::invalid_argument("Chyba při parsování řádku: " + radek + " - " + e.what());
    }

    return student;
}
void PridejStudentaNaKonec(Node** pHead, Student data)
{
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (*pHead == nullptr)
    {
        *pHead = newNode;
        return;
    }

    Node* current = *pHead;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    current->next = newNode;
}
void nactiStudentyZeSouboru(const std::string& studenti, Node** pHead)
{
    std::ifstream file(studenti);
    std::string radek;

    if (!file.is_open())
    {
        std::cerr << "Chyba při otevírání souboru: " << studenti << std::endl;
        return;
    }

    while (std::getline(file, radek))
    {
        if (radek.empty() || radek[0] == '#')
        {
            continue; // Ignoruj prázdné řádky a komentáře
        }

        try
        {
            Student student = parsujRadek(radek);
            PridejStudentaNaKonec(pHead, student);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Chyba při parsování řádku: " << radek << " - " << e.what() << std::endl;
        }
    }

    file.close();
}
void vypisSeznam(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << "ID: " << current->data.id
                  << ", Jméno: " << current->data.cele_jmeno
                  << ", Průměr: " << current->data.prumer << std::endl;
        current = current->next;
    }
}
void setridSeznamPodlePrumeru(Node* head)
{
    if (head == nullptr) return;

    bool swapped;
    do
    {
        swapped = false;
        Node* current = head;
        while (current->next != nullptr)
        {
            if (current->data.prumer > current->next->data.prumer)
            {
                std::swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}
void ulozStudentyDoSouboru(const std::string& studenti_serazeno, Node* head)
{
    std::ofstream file(studenti_serazeno);

    if (!file.is_open())
    {
        std::cerr << "Chyba při otevírání souboru pro zápis: " << studenti_serazeno << std::endl;
        return;
    }

    Node* current = head;
    while (current != nullptr)
    {
        file << current->data.id << ","
             << current->data.cele_jmeno << ","
             << current->data.prumer << std::endl;
        current = current->next;
    }

    file.close();
}
void zrusSeznam(Node** pHead)
{
    Node* current = *pHead;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    *pHead = nullptr;
}

int main()
{
    Node* head = nullptr;
    std::string input_file = "studenti.txt";
    std::string output_file = "studenti_serazeno.txt";

    nactiStudentyZeSouboru(input_file, &head);

    std::cout << "\n--- Před seřazením ---\n";
    vypisSeznam(head);

    PridejStudentaNaKonec(&head, Student{"Lukas Nevim", 1.6, 120});

    setridSeznamPodlePrumeru(head);

    std::cout << "\n--- Po seřazení ---\n";
    vypisSeznam(head);

    ulozStudentyDoSouboru(output_file, head);
    zrusSeznam(&head);

    return 0;
}



