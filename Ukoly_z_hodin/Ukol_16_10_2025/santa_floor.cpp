// This file contains logic to compute final floor and first basement position
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// Read input using ifstream only.
	// Priority: argv[1] (if given) -> "input.txt" in CWD -> "/dev/stdin"
	string data;
	ifstream in;
	if (argc > 1) {
		in.open(argv[1]);
		if (!in) {
			cerr << "Failed to open file: " << argv[1] << '\n';
			return 2;
		}
	} else {
		// try input.txt
		in.open("input.txt");
		if (!in) {
			// fallback to /dev/stdin
			in.clear();
			in.open("/dev/stdin");
			if (!in) {
				cerr << "Failed to open any input (tried input.txt and /dev/stdin)" << '\n';
				return 2;
			}
		}
	}

	// read whole file into string
	string line;
	while (getline(in, line)) {
		data += line;
	}

	// Remove whitespace (newlines, spaces) to accept pretty-printed input
	string instr;
	for (char c : data) if (c == '(' || c == ')') instr.push_back(c);

	int floor = 0;
	for (char c : instr) {
		if (c == '(') ++floor;
		else if (c == ')') --floor;
	}

	// Print only the final floor as an integer
	cout << floor << '\n';

	return 0;
}
