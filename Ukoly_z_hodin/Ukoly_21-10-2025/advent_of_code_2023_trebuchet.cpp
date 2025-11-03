#include <bits/stdc++.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream in;

    if (argc > 1)
    {
        in.open(argv[1]);
        if (!in)
        {
            cerr << "Failed to open file: " << argv[1] << '\n';
            return 2;
        }
    }
    else
    {
        in.open("input.txt");
        if (!in)
        {
            in.clear();
            in.open("/dev/stdin");
            if (!in)
            {
                cerr << "Failed to open any input" << '\n';
                return 2;
            }
        }
    }

    vector<string> slova = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string line;
    long long total = 0;

    while (getline(in, line))
    {
        vector<int> digits;  

        for (size_t i = 0; i < line.size(); ++i)
        {
            if (isdigit(line[i]))
            {
                digits.push_back(line[i] - '0');
            }
            for (int d = 0; d < 10; ++d)
            {
                const string &word = slova[d];
                if (i + word.size() <= line.size() && line.substr(i, word.size()) == word)
                {
                    digits.push_back(d);
                    break;
                }
            }
        }

        if (!digits.empty())
        {
            int value = digits.front() * 10 + digits.back();
            total += value;
        }
    }

    cout << "Total: " << total << '\n';
    return 0;
}
