#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <set>
#include <bits/stdc++.h>
using namespace std;

set<string> includes;
set<string> solved;
vector<string> order_solving;
vector<string> readLines(string reference) {
	ifstream fin;
	fin.open("Library/" + reference);
	if(!fin.is_open()) {
		cerr << "Dependency not found : " + reference << endl;
	}
	vector<string> lines;
	while(!fin.fail()) {
		string line;
		getline(fin, line);
		if(!fin.fail())
			lines.push_back(line);
	}
	fin.close();
	return lines;
}

vector<string> getWords(string line) {
	vector<string> words;
	words.push_back("");

	for(char car : line) {
		if(isspace(car)) {
			if(words.back() != "")
				words.push_back("");
		}
		else {
			words.back().push_back(car);
		}
	}

	if(words.back() == "") {
		words.pop_back();
	}

	return words;
}

vector<string> Parse_macro(string line, string macro) {
	vector<string> words = getWords(line);
	if(!words.empty() && words[0] == macro) {
		words.erase(words.begin());
		return words;
	}
	return vector<string>();
}

vector<string> Parse_macro(vector<string> lines, string macro) {
	vector<string> references;
	for(string line : lines) {
		vector<string> refs = Parse_macro(line, macro);
		if(macro=="#author" and (int)refs.size() > 0){
			refs.push_back("\n");
		}
		for(string ref : refs) {
			references.push_back(ref);
		}
	}
	return references;
}

vector<string> getDefinitions(vector<string> lines) {
	vector<string> definitions;
	for(string line : lines) {
		vector<string> words = getWords(line);
		definitions.push_back(line);
	}

	return definitions;
}

void genCode(vector<string> lines) {
	for(string line : lines) {
		vector<string> words = getWords(line);
		if(words.empty() || (words[0] != "#require" && words[0]!="#std_require" && words[0]!="#main" && words[0]!="#author")){
			cout << line << endl;
		}
	}
}

void dfs(vector<string> lines) {
	vector<string> refs = Parse_macro(lines, "#require");
	for(string ref : refs) {
		if(solved.find(ref) == solved.end()) {
			dfs(readLines(ref + ".h"));
			order_solving.push_back(ref);
			solved.insert(ref);
		}
	}
}

int main() {
	vector<string> lines;
	while(!cin.fail()) {
		string line;
		getline(cin, line);
		if(!cin.fail())
			lines.push_back(line);
	}

	vector<string> authcmt = (Parse_macro(lines , "#author"));
	dfs(lines);
	int n = authcmt.size();
	if(n){
		cout << "/*\n";
		int addtab = true;
		for(int i = 0; i < n; i++){
			if(addtab == true) cout << "    ",addtab = false;
			cout << authcmt[i];
			if(i!=n-1 and authcmt[i]!="\n") cout << " ";
			if(authcmt[i]=="\n" and i!=n-1) addtab = true;
		}
		cout << "*/\n";
	}
	
	cout << "#include \"bits/stdc++.h\"" << endl;
	cout << "using namespace std;" << endl;

	for(string ref : order_solving) {
		vector<string> definitions = getDefinitions(readLines(ref + ".h"));
		genCode(definitions);
	}
	genCode(lines);

	return 0;
}
