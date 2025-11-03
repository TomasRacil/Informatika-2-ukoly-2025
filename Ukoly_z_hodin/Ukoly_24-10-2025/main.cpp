#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student{
    int id;
    string name;
    float prumer;
};
struct Uzel{
    Student data;
    Uzel* dalsi;
};  
Student parsujRadek(const string& radek) {
    Student data;
    size_t pos1 = radek.find(',');
    size_t pos2 = radek.find(',', pos1 + 1);
    
    data.id = stoi(radek.substr(0, pos1));
    data.name = radek.substr(pos1 + 1, pos2 - pos1 - 1);
    data.prumer = stof(radek.substr(pos2 + 1));
    
    return data;
}
Student pridejStudentaNaKonec(Uzel*& pHead, const Student& data) {
    Uzel* novyUzel = new Uzel{data, nullptr};
    if (pHead == nullptr) {
        pHead = novyUzel;
    } else {
        Uzel* aktualni = pHead;
        while (aktualni->dalsi != nullptr) {
            aktualni = aktualni->dalsi;
        }
        aktualni->dalsi = novyUzel;
    }
    return data;
}
Student nactiStudentyZeSouboru(const string& nazevSouboru, Uzel*& pHead) {
    ifstream file(nazevSouboru);
    string radek;
    while (getline(file, radek)) {
        Student data = parsujRadek(radek);
        pridejStudentaNaKonec(pHead, data);
    }
    file.close();
    return Student{};
}
Student vypisSeznam(Uzel* pHead) {
    Uzel* aktualni = pHead;
    while (aktualni != nullptr) {
        cout << "ID: " << aktualni->data.id 
             << ", Jméno: " << aktualni->data.name 
             << ", Průměr: " << aktualni->data.prumer << endl;
        aktualni = aktualni->dalsi;
    }
    return Student{};
}
Student setridSeznamPodlePrumeru(Uzel*& pHead) {
    if (pHead == nullptr || pHead->dalsi == nullptr) {
        return Student{};
    }
    bool swapped;
    do {
        swapped = false;
        Uzel* aktualni = pHead;
        while (aktualni->dalsi != nullptr) {
            if (aktualni->data.prumer > aktualni->dalsi->data.prumer) {
                swap(aktualni->data, aktualni->dalsi->data);
                swapped = true;
            }
            aktualni = aktualni->dalsi;
        }
    } while (swapped);
    return Student{};
}
Student ulozStudentyDoSouboru(const string& nazevSouboru, Uzel* pHead){
    ofstream file(nazevSouboru);
    Uzel* aktualni = pHead;
    while (aktualni != nullptr) {
        file << aktualni->data.id << "," 
             << aktualni->data.name << "," 
             << aktualni->data.prumer << endl;
        aktualni = aktualni->dalsi;
    }
    file.close();
    return Student{};
}
Student ZrusSeznam(Uzel*& pHead){
    Uzel* aktualni = pHead;
    while (aktualni != nullptr) {
        Uzel* temp = aktualni;
        aktualni = aktualni->dalsi;
        delete temp;
    }
    pHead = nullptr;
    return Student{};
}
int main() {
    Uzel* seznamStudentu = nullptr;
    
    nactiStudentyZeSouboru("studenti.txt", seznamStudentu);
    cout << "Seznam studentů:" << endl;
    vypisSeznam(seznamStudentu);
    
    setridSeznamPodlePrumeru(seznamStudentu);
    cout << "\nSeznam studentů po setřídění podle průměru:" << endl;
    vypisSeznam(seznamStudentu);
    
    ulozStudentyDoSouboru("serazeni_studenti.txt", seznamStudentu);
    
    ZrusSeznam(seznamStudentu);
    return 0;
}