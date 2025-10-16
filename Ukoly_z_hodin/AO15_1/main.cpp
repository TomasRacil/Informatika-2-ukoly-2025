#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void clearConsole() {
    system("clear");
}

class  Floor{
    string input = "";

    void getFloor() {

        int iteration = 0;
        int floor = 0;
        for (char c : input) {
            if (c != '(' && c != ')') {
                continue;
            }
            
            iteration++;
            if (c == '(') {
                floor++;
            }
            else if (c == ')') {
                floor--;
            }
            if (floor == -1) {
                cout << "Basement reached at iteration " + to_string(iteration) + "\n";
            }
        }
        cout << "Floor " + to_string(floor) << "\n";
        cout << "Press enter to continue \n";
        cin.ignore();
        cin.get();
    }

public:

    void fromFile(string fileName) {
        ifstream file(fileName);
        if (file.is_open()) {
            getline(file, input);
            file.close();
            getFloor();
        } else {
            cout << "Could not open the file \n";
        }
    }

    void fromConsole() {
        cout << "Enter the input: ";
        cin >> input;
        getFloor();
    }
};

int main() {
    Floor f = Floor();

    REPL:
        clearConsole();
        cout << "Menu: \n";
        cout << "1. ze souboru \n";
        cout << "2. z console \n";
        cout << "3. Exit \n";

        string command;
        cin >> command;

        if (command == "1") {
            f.fromFile("/workspaces/Informatika-2-ukoly-2025-Kaplanek_Lukas/Ukoly_z_hodin/AO15_1/input.txt");

        } else if (command == "2") {
            f.fromConsole();

        } else if (command == "3") {
            return 0;
        } else {
            cout << "Not a valid option \n";
        }
    goto REPL;
}