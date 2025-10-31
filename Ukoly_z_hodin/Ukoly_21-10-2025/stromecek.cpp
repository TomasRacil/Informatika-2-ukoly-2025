#include <iostream>
using namespace std;

void drawTree(int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < height - i - 1; ++j) {
            cout << " ";
        }
        for (int k = 0; k < 2 * i + 1; ++k) {
            cout << "*";
        }
        cout << endl;
    }
    for (int i = 0; i < height - 1; ++i) {
        cout << " ";
    }
    cout << "*" << endl;
    for (int i = 0; i < height - 1; ++i) {
        cout << " ";
    }
    cout << "*" << endl;
}
int main() {
    int height;
    cout << "Velikost stromu: ";
    cin >> height;
    drawTree(height);
    return 0;
}