#include <iostream> //prida knihovnu iostream
#include <string>   //prida knihovnu string
#include <fstream>  //prida knihovnu fstream
#include <iomanip>
#include <sstream>

using namespace std;

// definuje strukturu Student
struct Student
{
    int id;
    string name; // noddy
    double prumer;
};
// definuje strukturu Node
struct Node
{
    Student student;
    Node *next;

    Node(Student newStudent)
    {
        student = newStudent;
        next = nullptr;
    }

    Node *operator[](int index)
    {
        Node *current = this;
        for (int i = 0; i < index; i++)
        {
            if (current == nullptr)
            {
                return nullptr;
            }
            current = current->next;
        }
        return current;
    }
};

Student parsujRadek(const string &radek)
{
    Student s;
    stringstream ss(radek);
    string idStr, nameStr, prumerStr;

    getline(ss, idStr, ',');
    getline(ss, nameStr, ',');
    getline(ss, prumerStr, ',');

    s.id = stoi(idStr);
    s.name = nameStr;
    s.prumer = stod(prumerStr);

    return s;
}

void zrusSeznam(Node **pHead)
{
    Node *current = *pHead;
    while (current != nullptr)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    *pHead = nullptr;
}

void vypisSeznam(Node *head)
{
    Node *current = head;
    while (current != nullptr)
    {
        cout << current->student.id << setw(5) << current->student.name << setw(5) << current->student.prumer << '\n';
        current = current->next;
    }
}

Node *pridejStudentaNaKonec(Node *head, Student new_Student)
{
    Node *newNode = new Node(new_Student);
    if (head == nullptr)
    {
        return newNode;
    }

    Node *last = head;

    while (last->next != nullptr)
    {
        last = last->next;
    }

    last->next = newNode;
    return head;
}

Node *NactiStudentyZeSouboru(const string &filename)
{
    ifstream soubor(filename);
    string radek;
    Node *head = nullptr;

    if (!soubor.is_open())
    {
        cout << "soubor se nepodařilo otevřít" << endl;
    }
    else
    {
        while (getline(soubor, radek))
        {
            if (radek.find("#") != 0 || radek.empty())
            {
                head = pridejStudentaNaKonec(head, parsujRadek(radek));
            }
        }
    }
    soubor.close();
    return head;
}

void setridSeznamPodlePrumeru(Node *head)
{
    for (Node *i = head; i != nullptr; i = i->next)
    {
        Node *minNode = i;
        for (Node *j = i->next; j != nullptr; j = j->next)
        {
            if (j->student.prumer < minNode->student.prumer)
            {
                minNode = j;
            }
        }
        if (minNode != i)
        {
            swap(i->student, minNode->student);
        }
    }
}
void ulozStudentyDoSouboru(const string &studenti_serazeno, Node *head)
{
    ofstream file(studenti_serazeno);

    if (!file.is_open())
    {
        cerr << "Chyba pri otevirani souboru" << studenti_serazeno << endl;
        return;
    }
    Node *current = head;
    while (current != nullptr)
    {
        file << current->student.id << ","
             << current->student.name << ","
             << current->student.prumer << endl;
        current = current->next;
    }
    file.close();
}

// entry point
int main()
{
    string input_file = "studenti.txt";
    string output_file = "studenti_serazeno.txt";

    Node *head = NactiStudentyZeSouboru(input_file);

    cout << "\n Pred serazenim \n";
    vypisSeznam(head);

    setridSeznamPodlePrumeru(head);

    cout << "\n Po serazeni \n";
    vypisSeznam(head);

    Student st = parsujRadek("111, Karel Hajek, 4.3");

    pridejStudentaNaKonec(head, st);

    ulozStudentyDoSouboru(output_file, head);

    // JAKMILE BUDE NĚKDO DOPLŇOVAT DO MAINU NAHRADÍ TÍM MŮJ COMMENT
    // pridat zaznam na konec: "111, Karel Hajek, 4.3"
    // doplnit vypisSeznam
    // vytvorit serazeny seznam
    // zapsat serazeny seznam
    zrusSeznam(&head);
    return 0;
}