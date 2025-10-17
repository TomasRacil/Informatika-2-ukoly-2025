#include <iostream>
using namespace std;

int main() {
    string text;
    cout << "Zadej zavorky: ";
    cin >> text;

    int patro = 0;
    int prvni = -1;

    for (int i = 0; i < text.size(); i++) {
        if (text[i] == '(') patro++;
        if (text[i] == ')') patro--;

        if (patro < 0 && prvni == -1)
            prvni = i + 1;
    }

    cout << "Konecne patro: " << patro << endl;

    if (prvni == -1)
        cout << "Do suterenu jsi nikdy nespadl." << endl;
    else
        cout << "Poprve jsi spadl do suterenu na pozici: " << prvni << endl;

    return 0;
}