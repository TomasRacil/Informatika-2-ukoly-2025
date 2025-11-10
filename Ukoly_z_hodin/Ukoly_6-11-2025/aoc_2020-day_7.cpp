#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
using namespace std;

static string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

int main(int argc, char** argv) {
    const string filename = (argc > 1) ? argv[1] : "data.txt";
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Cannot open file: " << filename << "\n";
        return 1;
    }

    unordered_map<string, vector<string>> parents;
    unordered_map<string, vector<pair<string,int>>> children;

    string line;
    while (getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;
        size_t pos = line.find(" bags contain ");
        if (pos == string::npos) continue;
        string parent = line.substr(0, pos);
        string rest = line.substr(pos + string(" bags contain ").size());
        if (rest.find("no other bag") != string::npos) {
            children[parent] = {};
            continue;
        }

        //splt ,
        stringstream ss(rest);
        string part;
        while (getline(ss, part, ',')) {
            part = trim(part);

            if (!part.empty() && part.back() == '.') part.pop_back();
            size_t bagPos = part.find(" bag");
            if (bagPos != string::npos) part = part.substr(0, bagPos);
            part = trim(part);
            stringstream pss(part);
            int count;
            if (!(pss >> count)) continue;
            string color;
            getline(pss, color);
            color = trim(color);
            if (!color.empty()) {
                parents[color].push_back(parent);
                children[parent].push_back({color, count});
            }
        }
    }
    in.close();

    // Part 1: 
    const string target = "shiny gold";
    queue<string> q;
    set<string> seen;
    q.push(target);

    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        auto it = parents.find(cur);
        if (it == parents.end()) continue;
        for (const auto &p : it->second) {
            if (seen.insert(p).second) {
                q.push(p);
            }
        }
    }

    cout << "Part 1 - Number of bag colors that can eventually contain \"" << target << "\": " << seen.size() << "\n";

    // Part 2: 
    unordered_map<string, long long> memo;
    function <long long(const string&)> count_inside = [&](const string &color) -> long long {
        auto mit = memo.find(color);
        if (mit != memo.end()) return mit->second;
        long long total = 0;
        auto cit = children.find(color);
        if (cit == children.end() || cit->second.empty()) {
            memo[color] = 0;
            return 0;
        }
        for (const auto &pr : cit->second) {
            const string &child = pr.first;
            int cnt = pr.second;
            total += cnt * (1 + count_inside(child));
        }
        memo[color] = total;
        return total;
    };

    cout << "Part 2 - Total bags required inside \"" << target << "\": " << count_inside(target) << "\n";

    return 0;
}