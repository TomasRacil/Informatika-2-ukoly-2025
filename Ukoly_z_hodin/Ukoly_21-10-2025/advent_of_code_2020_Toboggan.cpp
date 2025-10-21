#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> read_map(const string& filename) {
    vector<string> map;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Nemozno otvorit subor" << filename << endl;
        exit(1);
    }

    while (getline(file, line)) {
        if (!line.empty()) {
            map.push_back(line);
        }
    }

    file.close();
    return map;
}

long long count_trees(const vector<string>& map, int right, int down) {
    int width = map[0].size();
    int height = map.size();
    int x = 0, y = 0;
    long long tree_count = 0;

    while (y < height) {
        if (map[y][x % width] == '#') {
            tree_count++;
        }
        x += right;
        y += down;
    }

    return tree_count;
}

int main() {
    string filename = "tobogan.txt";
    vector<string> map = read_map(filename);

    vector<pair<int, int>> slopes = {
        {1, 1}, //prvni doprava -> , druha dolu
        {3, 1},
        {5, 1},
        {7, 1},
        {1, 2}
    };

    long long result = 1;

    for (const auto& slope : slopes) {
        long long trees = count_trees(map, slope.first, slope.second);
        cout << "Do prava:" << slope.first << ", dolu: " << slope.second
             << " => pocet stromov: " << trees << endl;
        result *= trees;
    }

    cout << "Nasobok vsetkych stromov: " << result << endl;

    return 0;
}
