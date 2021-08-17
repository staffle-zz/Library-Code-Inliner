#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> lines;
    while (!cin.fail()) {
        string line;
        getline(cin, line);
        if (!cin.fail()) lines.push_back(line);
    }
    vector<string> bs = {"dbg", "db", "assrt", "dbgl"};
    vector<string> code;
    for (auto &line : lines) {
        int pos = 0;
        while (pos < line.length() and line[pos] == ' ') pos++;
        if (any_of(bs.begin(), bs.end(), [&](string j) { return (line.substr(pos, j.length()) == j); })) {
            continue;
        } else {
            code.push_back(line);
        }
    }

    for (auto line : code) cout << line << endl;
    return 0;
}
