#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

  
    string data;
    ifstream in;
    if (argc > 1) {
        in.open(argv[1]);
        if (!in) {
            cerr << "Failed to open file: " << argv[1] << '\n';
            return 2;
        }
    } else {
        
        in.open("input.txt");
        if (!in) {
            in.clear();
            in.open("/dev/stdin");
            if (!in) {
                cerr << "Failed to open any input" << '\n';
                return 2;
            }
        }
    }

    string line;
    while (getline(in, line)) {
        data += line;
    }

    string instr;
    for (char c : data) if (c == '(' || c == ')') instr.push_back(c);

    int floor = 0;
    int first_basement_pos = -1; 
    for (size_t i = 0; i < instr.size(); ++i) {
        if (instr[i] == '(') ++floor;
        else if (instr[i] == ')') --floor;

        if (floor < 0 && first_basement_pos == -1) {
            first_basement_pos = (int)i + 1;
        }
    }

    cout << "Final floor: " << floor << '\n';
    if (first_basement_pos == -1) {
        cout << "First entered basement: never\n";
    } else {
        cout << "First entered basement at position: " << first_basement_pos << '\n';
    }

    return 0;
}