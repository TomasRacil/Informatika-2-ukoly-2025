#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

  
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
    int total = 0;
    while (getline(in, line)) {
        char first = '\0', last = '\0';
        for (char c : line){
            if (isdigit(c)) {
                if (!first) first = c;
                last = c;
            }
        }
        if (first && last) {
            int value = (first - '0') *10 + (last - '0');
            total += value;
        }
        
    }
    cout << "Total: " << total << '\n';
    return 0;
}