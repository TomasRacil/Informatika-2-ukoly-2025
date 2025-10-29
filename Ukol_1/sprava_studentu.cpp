#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


struct Student {
    int id;
    string jmeno;
    double prumer;
};

//pro hezky vypis, pretizeni operatoru
ostream& operator<<(ostream& os, const Student& s) {
    os << "ID: " << s.id 
       << ", Jméno: " << s.jmeno 
       << ", Průměr: " << s.prumer;
    return os;
}


struct Uzel {
    Student data;
    Uzel* dalsi;
};


Student parsujRadek(const string& radek) {
    Student s{};
    stringstream ss(radek);
    string idStr, jmenoStr, prumerStr;

    try {
        // oddeleni podle carek
        if (!getline(ss, idStr, ',')) throw runtime_error("Chyba: chybí ID");
        if (!getline(ss, jmenoStr, ',')) throw runtime_error("Chyba: chybí jméno");
        if (!getline(ss, prumerStr, ',')) throw runtime_error("Chyba: chybí průměr");

        // orezani mezer kolem jmena
        while (!jmenoStr.empty() && jmenoStr.front() == ' ') jmenoStr.erase(0, 1);
        while (!jmenoStr.empty() && jmenoStr.back() == ' ') jmenoStr.pop_back();

        s.id = stoi(idStr);
        s.jmeno = jmenoStr;
        s.prumer = stod(prumerStr);
    }
    catch (const exception& e) {
        cerr << "Chyba při parsování řádku: \"" << radek << "\" (" << e.what() << ")" << endl;
    }

    return s;
}


void pridejStudentaNaKonec(Uzel** pHead, const Student& data) {
    Uzel* novy = new Uzel{ data, nullptr };

    if (*pHead == nullptr) {
        *pHead = novy;
        return;
    }

    Uzel* temp = *pHead;
    while (temp->dalsi != nullptr)
        temp = temp->dalsi;

    temp->dalsi = novy;
}


void nactiStudentyZeSouboru(const string& nazevSouboru, Uzel** pHead) {
    ifstream soubor(nazevSouboru);
    if (!soubor.is_open()) {
        cerr << "Nelze otevřít soubor: " << nazevSouboru << endl;
        return;
    }

    string radek;
    while (getline(soubor, radek)) {
        if (radek.empty() || radek[0] == '#') continue; // přeskočit prázdné nebo komentáře

        Student s = parsujRadek(radek);
        if (s.id != 0) // jen pokud má smysluplné ID
            pridejStudentaNaKonec(pHead, s);
    }

    soubor.close();
}


void vypisSeznam(Uzel* head) {
    if (!head) {
        cout << "Seznam je prázdný." << endl;
        return;
    }

    cout << "\n--- Výpis seznamu studentů ---\n";
    Uzel* temp = head;
    while (temp != nullptr) {
        cout << temp->data << endl;
        temp = temp->dalsi;
    }
    cout << "-------------------------------\n";
}


void prohodData(Student& a, Student& b) {
    Student tmp = a;
    a = b;
    b = tmp;
}


void setridSeznamPodlePrumeru(Uzel* head) {
    if (!head) return;

    bool swapped;
    Uzel* ptr1;
    Uzel* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->dalsi != lptr) {
            if (ptr1->data.prumer > ptr1->dalsi->data.prumer) {
                prohodData(ptr1->data, ptr1->dalsi->data);
                swapped = true;
            }
            ptr1 = ptr1->dalsi;
        }
        lptr = ptr1;
    } while (swapped);
}


void ulozStudentyDoSouboru(const string& nazevSouboru, Uzel* head) {
    ofstream soubor(nazevSouboru);
    if (!soubor.is_open()) {
        cerr << "Nelze otevřít soubor pro zápis: " << nazevSouboru << endl;
        return;
    }

    Uzel* temp = head;
    while (temp != nullptr) {
        soubor << temp->data.id << ", " 
               << temp->data.jmeno << ", " 
               << temp->data.prumer << endl;
        temp = temp->dalsi;
    }

    soubor.close();
}


void zrusSeznam(Uzel** pHead) {
    Uzel* current = *pHead;
    while (current != nullptr) {
        Uzel* dalsi = current->dalsi;
        delete current;
        current = dalsi;
    }
    *pHead = nullptr;
}


int main() {
    Uzel* head = nullptr;

    string vstup = "studenti.txt";
    string vystup = "studenti_serazeno.txt";

    nactiStudentyZeSouboru(vstup, &head);
    vypisSeznam(head);

    Student novy{111, "Roman Vavra", 1.6};
    pridejStudentaNaKonec(&head, novy);

    cout << "\nPo přidání nového studenta:\n";
    vypisSeznam(head);

    setridSeznamPodlePrumeru(head);
    cout << "\nPo seřazení podle průměru:\n";
    vypisSeznam(head);

    ulozStudentyDoSouboru(vystup, head);

    zrusSeznam(&head);
    return 0;
}
