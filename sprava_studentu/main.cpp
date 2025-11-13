#include <iostream> 
#include <string>   
#include <fstream> 
#include <iomanip>
#include <sstream>

using namespace std;

// definuje strukturu Student
struct Student {
    int id;
    string name;
    double prumer;
};

// definuje strukturu Node
struct Node {
    Student student;
    Node* next;

    Node(Student newStudent) {
        student = newStudent;
        next = nullptr;
    }

    Node* operator[](int index) {
        Node* current = this;
        for (int i = 0; i < index; i++) {
            if (current == nullptr) {
                return nullptr;
            }
            current = current->next;
        }
        return current;
    }
};

// 🌿 Přidá studenta na konec seznamu
Node* pridejStudentaNaKonec(Node* head, Student new_Student) {
    Node* newNode = new Node(new_Student);
    if (head == nullptr) {
        return newNode;
    }

    Node* last = head;
    while (last->next != nullptr) {
        last = last->next;
    }
    last->next = newNode;
    return head;
}

// 🌿 Parsuje řádek textu do struktury Student
Student parsujRadek(const string& radek) {
    Student s;
    stringstream ss(radek);
    string idStr, nameStr, prumerStr;

    getline(ss, idStr, ',');
    getline(ss, nameStr, ',');
    getline(ss, prumerStr, ',');

    // odstranění mezer kolem jména
    if (!nameStr.empty() && nameStr[0] == ' ')
        nameStr.erase(0, 1);

    s.id = stoi(idStr);
    s.name = nameStr;
    s.prumer = stod(prumerStr);

    return s;
}

// 🌿 Načte studenty ze souboru a uloží je do spojového seznamu
Node* NactiStudentyZeSouboru(const string& filename) {
    ifstream soubor(filename);
    string radek;
    Node* head = nullptr;

    if (!soubor.is_open()) {
        cout << "Soubor se nepodarilo otevrit." << endl;
        return nullptr;
    }

    while (getline(soubor, radek)) {
        if (radek.empty() || radek[0] == '#') continue;
        Student s = parsujRadek(radek);
        head = pridejStudentaNaKonec(head, s);
    }

    soubor.close();
    return head;
}

// 🌿 Vypíše seznam studentů
void vypisSeznam(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->student.id << "\t"
             << current->student.name << "\t"
             << fixed << setprecision(2) << current->student.prumer << '\n';
        current = current->next;
    }
}

// 🌿 Seřadí seznam podle průměru (výběrové řazení)
void setridSeznamPodlePrumeru(Node* head) {
    for (Node* i = head; i != nullptr; i = i->next) {
        Node* minNode = i;
        for (Node* j = i->next; j != nullptr; j = j->next) {
            if (j->student.prumer < minNode->student.prumer) {
                minNode = j;
            }
        }
        if (minNode != i) {
            swap(i->student, minNode->student);
        }
    }
}

// 🌿 Uloží seznam studentů do souboru
void ulozStudentyDoSouboru(const string& filename, Node* head) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Chyba pri otevirani souboru: " << filename << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        file << current->student.id << ","
             << current->student.name << ","
             << current->student.prumer << endl;
        current = current->next;
    }

    file.close();
}

// 🌿 Uvolní celý spojový seznam z paměti
void zrusSeznam(Node** pHead) {
    Node* current = *pHead;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    *pHead = nullptr;
}

// 🚀 entry point
int main() {
    string input_file = "studenti.txt";
    string output_file = "studenti_serazeno.txt";

    Node* head = NactiStudentyZeSouboru(input_file);

    if (head == nullptr) {
        cout << "Seznam je prazdny nebo se nepodarilo nacist data." << endl;
        return 0;
    }

    cout << "\n--- Pred serazenim ---\n";
    vypisSeznam(head);

    setridSeznamPodlePrumeru(head);

    cout << "\n--- Po serazeni ---\n";
    vypisSeznam(head);

    ulozStudentyDoSouboru(output_file, head);

    zrusSeznam(&head);
    return 0;
}
