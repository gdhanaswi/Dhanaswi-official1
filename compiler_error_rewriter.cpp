#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <sstream>

using namespace std;

/* ================================
   WEEK 5 – DATA MODELS (IR DESIGN)
   ================================ */

struct Token {
    string type;
    string value;
    int line;
};

struct Statement {
    string stmtType;     // Declaration, Assignment, Return
    vector<Token> tokens;
    int lineNumber;
};

struct ErrorNode {
    string rawMessage;
    string classifiedType;
    int lineNumber;
};

struct IR {
    vector<Statement> statements;
    vector<ErrorNode> errors;
};

/* ================================
   WEEK 2 & 7 – ERROR CLASSIFICATION
   ================================ */

string classifyError(const string &errorMsg) {
    if (errorMsg.find("expected ';'") != string::npos)
        return "MissingSemicolon";

    if (errorMsg.find("not declared") != string::npos)
        return "UndeclaredVariable";

    if (errorMsg.find("division by zero") != string::npos)
        return "DivisionByZero";

    return "UnknownError";
}

/* ================================
   WEEK 7 – EXPLANATION GENERATOR
   ================================ */

void generateExplanation(const string &errorType) {

    cout << "\n--- Human Friendly Explanation ---\n";

    if (errorType == "MissingSemicolon") {
        cout << "You forgot to add a semicolon at the end of the statement.\n";
        cout << "Fix: Add ';' at the end of the line.\n";
    }
    else if (errorType == "UndeclaredVariable") {
        cout << "A variable is used before declaration.\n";
        cout << "Fix: Declare the variable before using it.\n";
    }
    else if (errorType == "DivisionByZero") {
        cout << "Division by zero is not allowed.\n";
        cout << "Fix: Ensure denominator is not zero.\n";
    }
    else {
        cout << "Unknown error type. Please check your code carefully.\n";
    }
}

/* ================================
   WEEK 6 – BASIC PARSING
   ================================ */

Statement parseLine(string line, int lineNumber) {

    Statement stmt;
    stmt.lineNumber = lineNumber;

    stringstream ss(line);
    string word;
    vector<string> words;

    while (ss >> word)
        words.push_back(word);

    if (words.size() == 0) {
        stmt.stmtType = "Empty";
        return stmt;
    }

    if (words[0] == "int" || words[0] == "float" || words[0] == "double") {
        stmt.stmtType = "Declaration";
        stmt.tokens.push_back({"keyword", words[0], lineNumber});
        if (words.size() > 1)
            stmt.tokens.push_back({"identifier", words[1], lineNumber});
    }
    else if (words[0] == "return") {
        stmt.stmtType = "Return";
        stmt.tokens.push_back({"keyword", "return", lineNumber});
    }
    else {
        stmt.stmtType = "Assignment";
        stmt.tokens.push_back({"identifier", words[0], lineNumber});
    }

    return stmt;
}

/* ================================
   WEEK 8 – DATA FLOW ANALYSIS
   ================================ */

void dataFlowAnalysis(IR &ir) {

    cout << "\n--- Data Flow Analysis ---\n";

    set<string> symbolTable;

    for (auto &stmt : ir.statements) {

        if (stmt.stmtType == "Declaration" && stmt.tokens.size() > 1) {
            symbolTable.insert(stmt.tokens[1].value);
        }

        if (stmt.stmtType == "Assignment" && stmt.tokens.size() > 0) {
            string var = stmt.tokens[0].value;
            if (symbolTable.find(var) == symbolTable.end()) {
                cout << "Error: Variable '" << var
                     << "' used before declaration (Line "
                     << stmt.lineNumber << ")\n";
            }
        }
    }
}

/* ================================
   WEEK 8 – CONTROL FLOW ANALYSIS
   ================================ */

void controlFlowAnalysis(IR &ir) {

    cout << "\n--- Control Flow Analysis ---\n";

    bool returnFound = false;

    for (auto &stmt : ir.statements) {
        if (stmt.stmtType == "Return")
            returnFound = true;
    }

    if (!returnFound) {
        cout << "Warning: No return statement found.\n";
    }
}

/* ================================
   WEEK 8 – PATTERN DETECTION
   ================================ */

void patternDetection(IR &ir) {

    cout << "\n--- Pattern Detection ---\n";

    for (auto &error : ir.errors) {
        error.classifiedType = classifyError(error.rawMessage);
        cout << "Detected Error Type: " << error.classifiedType << endl;
    }
}

/* ================================
   MAIN FUNCTION – INTEGRATION
   ================================ */

int main() {

    IR ir;

    cout << "Enter number of code lines: ";
    int n;
    cin >> n;
    cin.ignore();

    cout << "Enter your C++ code:\n";

    for (int i = 1; i <= n; i++) {
        string line;
        getline(cin, line);
        ir.statements.push_back(parseLine(line, i));
    }

    cout << "\nEnter compiler error message: ";
    string errorMsg;
    getline(cin, errorMsg);

    ErrorNode errorNode;
    errorNode.rawMessage = errorMsg;
    errorNode.lineNumber = 1;

    ir.errors.push_back(errorNode);

    /* ===== Perform Analysis ===== */

    dataFlowAnalysis(ir);
    controlFlowAnalysis(ir);
    patternDetection(ir);

    /* ===== Generate Explanation ===== */

    if (!ir.errors.empty()) {
        generateExplanation(ir.errors[0].classifiedType);
    }

    cout << "\n--- Program Completed Successfully ---\n";

    return 0;
}
