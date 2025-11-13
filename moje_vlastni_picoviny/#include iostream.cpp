#include <iostream>
#include <string>
using namespace std;

int main(){
    string rock;
    string paper;
    string scissors;

    cout << "Enter rock, paper, or scissors: ";
    cin >> rock >> paper >> scissors;

    cout << "You entered: " << rock << ", " << paper << ", " << scissors << endl;
    return 0;
}