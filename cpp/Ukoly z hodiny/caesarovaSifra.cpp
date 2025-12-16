#include <iostream>
#include <string>

using namespace std;

string caesarEncrypt(const string &text, int key) {
    string result = "";
    key = key % 26;

    for (char c : text) {
        if (c >= 'a' && c <= 'z') {
            c = ((c - 'a' + key) % 26) + 'a';
        }
        result += c;
    }
    return result;
}


int main() {
    string text;
    int key;
    int volba;

    cout << "Caesarova sifra" << endl;
    cout << "1 - Sifrovat" << endl;
    cin >> volba;

    cin.ignore();
    cout << "Zadej text: ";
    getline(cin, text);

    cout << "Zadej klic (0-25): ";
    cin >> key;

    return 0;
}
