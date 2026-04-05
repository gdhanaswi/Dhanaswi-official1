#include <iostream>
#include <unordered_map>
#include <set>
using namespace std;

/* ==============================
   Optimized Error Map
   ============================== */

unordered_map<string, string> errorMap = {
    {"expected ';'", "MissingSemicolon"},
    {"not declared", "UndeclaredVariable"},
    {"division by zero", "DivisionByZero"},
    {"expected ')'", "MissingBracket"}
};

/* ==============================
   Optimized Error Classification
   ============================== */

string classifyError(const string &msg) {

    for (auto &entry : errorMap) {
        if (msg.find(entry.first) != string::npos)
            return entry.second;
    }

    return "UnknownError";
}

/* ==============================
   Secure Explanation Generator
   ============================== */

void generateExplanation(const string &type) {

    cout << "\n--- Secure Explanation ---\n";

    if (type == "MissingSemicolon") {
        cout << "Missing semicolon detected.\n";
        cout << "Fix: Add ';' only at the end of the statement.\n";
    }
    else if (type == "UndeclaredVariable") {
        cout << "Variable used without declaration.\n";
        cout << "Fix: Declare variable before usage.\n";
    }
    else if (type == "DivisionByZero") {
        cout << "Division by zero detected.\n";
        cout << "Fix: Check denominator before division.\n";
    }
    else if (type == "MissingBracket") {
        cout << "Missing closing parenthesis.\n";
        cout << "Fix: Add ')' at correct position.\n";
    }
    else {
        cout << "Unknown error. Verify code carefully.\n";
    }
}

/* ==============================
   Security Validation
   ============================== */

bool validateInput(const string &msg) {

    if (msg.empty()) {
        cout << "Error: Empty input not allowed.\n";
        return false;
    }

    if (msg.length() > 200) {
        cout << "Error: Input too long.\n";
        return false;
    }

    return true;
}

/* ==============================
   Data Flow Security Check
   ============================== */

void checkSecurity() {

    set<string> variables = {"x"}; // declared variables

    string usedVar = "y";

    if (variables.find(usedVar) == variables.end()) {
        cout << "\nSecurity Warning: Variable '" << usedVar
             << "' used before declaration.\n";
    }
}

/* ==============================
   MAIN FUNCTION
   ============================== */

int main() {

    string errorMsg;

    cout << "Enter compiler error message:\n";
    getline(cin, errorMsg);

    // Security Validation
    if (!validateInput(errorMsg))
        return 0;

    // Optimized Classification
    string type = classifyError(errorMsg);

    cout << "\nDetected Error Type: " << type << endl;

    // Secure Explanation
    generateExplanation(type);

    // Security Check
    checkSecurity();

    cout << "\n--- Optimization & Security Completed ---\n";

    return 0;
}
