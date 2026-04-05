#include <iostream>
#include <sstream>
#include <set>
using namespace std;

set<string> declaredVars;

// Trim helper
string trim(const string &s) {
    int start = s.find_first_not_of(" \t");
    int end = s.find_last_not_of(" \t");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

// Check if line ends with semicolon (basic syntax check)
bool hasSemicolon(const string &line) {
    string t = trim(line);
    return t.empty() || t.back() == ';' || t.back() == '{' || t.back() == '}';
}

void processLine(string line, int lineNo) {
    string t = trim(line);

    // Variable declaration
    if (t.find("int ") == 0) {
        string var = t.substr(4, t.find(';') - 4);
        declaredVars.insert(var);
        if (!hasSemicolon(t)) {
            cout << "Syntax Error (Line " << lineNo
                 << "): Missing semicolon after declaration.\n";
        }
    }
    // Assignment
    else if (t.find("=") != string::npos) {
        string var = trim(t.substr(0, t.find("=")));
        if (declaredVars.find(var) == declaredVars.end()) {
            cout << "Semantic Error (Line " << lineNo
                 << "): Variable '" << var << "' used without declaration.\n";
        }
        if (!hasSemicolon(t)) {
            cout << "Syntax Error (Line " << lineNo
                 << "): Missing semicolon after assignment.\n";
        }
    }
}

int main() {
    cout << "Enter C++ code (type END to stop):\n";
    string line;
    int lineNo = 1;

    while (getline(cin, line)) {
        if (line == "END") break;
        processLine(line, lineNo++);
    }

    cout << "\nParsing completed.\n";
    return 0;
}
