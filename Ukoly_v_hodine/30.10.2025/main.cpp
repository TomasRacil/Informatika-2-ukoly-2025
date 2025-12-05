#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream soubor("data.txt"); // open the file

    if (!soubor.is_open()) { // check if file opened successfully
        cerr << "Error: Could not open file 'data.txt'" << endl;
        return 1; // exit program with error code
    }

    string line;
    while (getline(soubor, line)) { // read line by line
        cout << line << endl;       // print each line
    }

    soubor.close(); // optional, closes automatically when out of scope
    return 0;
}
