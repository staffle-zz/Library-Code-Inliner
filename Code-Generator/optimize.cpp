#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include "bits/stdc++.h"
using namespace std;

set<string> includes;
set<string> solved;
vector<string> order_solving;

vector<string> readLines(string reference) {
    ifstream fin;
    fin.open("Library/" + reference);
    if (!fin.is_open()) { cerr << "Dependency not found : " + reference << endl; }
    vector<string> lines;
    while (!fin.fail()) {
        string line;
        getline(fin, line);
        if (!fin.fail()) lines.push_back(line);
    }
    fin.close();
    return lines;
}

vector<string> getWords(string line) {
    vector<string> words;
    words.push_back("");

    for (char car : line) {
        if (isspace(car)) {
            if (words.back() != "") words.push_back("");
        } else {
            words.back().push_back(car);
        }
    }

    if (words.back() == "") { words.pop_back(); }

    return words;
}

vector<string> Parse_macro(string line, string macro) {
    vector<string> words = getWords(line);
    if (!words.empty() && words[0] == macro) {
        words.erase(words.begin());
        return words;
    }
    return vector<string>();
}

vector<string> Parse_macro(vector<string> lines, string macro) {
    vector<string> references;
    for (string line : lines) {
        vector<string> refs = Parse_macro(line, macro);
        for (string ref : refs) { references.push_back(ref); }
    }
    return references;
}

vector<string> getDefinitions(vector<string> lines) {
    vector<string> definitions;
    for (string line : lines) {
        vector<string> words = getWords(line);
        definitions.push_back(line);
    }
    return definitions;
}

void genCode(vector<string> lines, ostream &out) {
    for (string line : lines) {
        vector<string> words = getWords(line);
        if (words.empty() || (words[0] != "#require" && words[0] != "#std_require" && words[0] != "#main" && words[0] != "#cases")) {
            out << line << endl;
        }
    }
}

void dfs(vector<string> lines) {
    vector<string> refs = Parse_macro(lines, "#require");
    for (string ref : refs) {
        if (solved.find(ref) == solved.end()) {
            dfs(readLines(ref + ".h"));
            order_solving.push_back(ref);
            solved.insert(ref);
        }
    }
}
time_t now = time(0);
char *dt = ctime(&now);

void add_dt(ostream &fout) {
    fout << "/**\n";
    fout << "* author  : amit_dwivedi\n";
    fout << "* created : " << dt;
    fout << "**/\n";
}
void add_prefix(ostream &fout) {
    fout << "#include \"bits/stdc++.h\"" << endl;
    fout << "using namespace std;" << endl;
}
vector<string> macros_used;
vector<string> lines;
void optimize_macros(map<string, bool> &mask) {
    vector<string> definitions_ = getDefinitions(readLines("macro.h"));
    int m = definitions_.size();
    vector<bool> used(m, true);

    for (int i = 0; i < m; ++i) {
        used[i] = false;
        ofstream fout("temp.cpp");
        add_prefix(fout);
        for (string ref : order_solving) {
            if (mask[ref] == false) continue;
            vector<string> definitions;
            if (ref == "macro") {
                for (int j = 0; j < m; ++j) {
                    if (used[j] == true) definitions.push_back(definitions_[j]);
                }
            } else {
                definitions = getDefinitions(readLines(ref + ".h"));
            }
            genCode(definitions, fout);
        }
        genCode(lines, fout);
        if (system("sh check.sh") != 0) {
            used[i] = true;
            macros_used.push_back(definitions_[i]);
        }
    }
}
int main() {
    while (!cin.fail()) {
        string line;
        getline(cin, line);
        if (!cin.fail()) lines.push_back(line);
    }

    dfs(lines);

    map<string, bool> mask;
    for (auto i : order_solving) { mask[i] = 1; }
    int n = order_solving.size();

    for (int i = n - 1; i >= 0; --i) {
        mask[order_solving[i]] = false;

        ofstream fout("temp.cpp");
        add_prefix(fout);
        for (string ref : order_solving) {
            if (mask[ref] == false) continue;
            vector<string> definitions = getDefinitions(readLines(ref + ".h"));
            genCode(definitions, fout);
            fout << "\n";
        }
        genCode(lines, fout);
        if (system("sh check.sh") != 0) {
            mask[order_solving[i]] = 1;
            if (order_solving[i] == "macro") { optimize_macros(mask); }
        }
    }

    ofstream gout("submit.cpp");
    add_dt(gout);
    add_prefix(gout);
    for (string ref : order_solving) {
        if (mask[ref] == false) continue;
        vector<string> definitions;
        if (ref == "macro") {
            definitions = macros_used;
        } else
            definitions = getDefinitions(readLines(ref + ".h"));
        genCode(definitions, gout);
        gout << "\n";
    }
    genCode(lines, gout);

    return 0;
}
