#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

// Token Structure
struct Token {
    string type;
    string value;
    int line;
};

// Statement Structure
struct Statement {
    string stmtType;
    vector<Token> tokens;
    int lineNumber;
};

// Error Structure
struct ErrorNode {
    string rawMessage;
    string classifiedType;
    int lineNumber;
};

// IR Container
struct IR {
    vector<Statement> statements;
    vector<ErrorNode> errors;
};

// Symbol Table for Data Flow
set<string> symbolTable;

// Data Flow Analysis
void dataFlowAnalysis(IR &ir) {
    cout << "\n--- Data Flow Analysis ---\n";

    for (auto &stmt : ir.statements) {
        if (stmt.stmtType == "Declaration") {
            symbolTable.insert(stmt.tokens[1].value);
        }

        if (stmt.stmtType == "Assignment") {
            string var = stmt.tokens[0].value;
            if (symbolTable.find(var) == symbolTable.end()) {
                cout << "Data Flow Error (Line " << stmt.lineNumber
                     << "): Variable '" << var << "' used before declaration.\n";
            }
        }
    }
}

// Control Flow Analysis
void controlFlowAnalysis(IR &ir) {
    cout << "\n--- Control Flow Analysis ---\n";

    bool returnFound = false;
    for (auto &stmt : ir.statements) {
        if (stmt.stmtType == "Return") {
            returnFound = true;
        }
    }

    if (!returnFound) {
        cout << "Warning: Function may exit without returning a value.\n";
    }
}

// Pattern Detection
void patternDetection(IR &ir) {
    cout << "\n--- Pattern Detection ---\n";

    for (auto &error : ir.errors) {
        if (error.rawMessage.find("expected ';'") != string::npos) {
            error.classifiedType = "MissingSemicolon";
            cout << "Pattern Matched: Missing Semicolon (Line "
                 << error.lineNumber << ")\n";
        }
    }
}

int main() {
    IR ir;

    // Sample Statements
    Statement s1 = {"Declaration", {{"keyword","int",1}, {"identifier","x",1}}, 1};
    Statement s2 = {"Assignment", {{"identifier","y",2}, {"operator","=",2}}, 2};
    Statement s3 = {"Return", {{"keyword","return",3}}, 3};

    ir.statements.push_back(s1);
    ir.statements.push_back(s2);
    ir.statements.push_back(s3);

    // Sample Error
    ErrorNode e1 = {"error: expected ';' before 'return'", "", 1};
    ir.errors.push_back(e1);

    // Perform Analysis
    dataFlowAnalysis(ir);
    controlFlowAnalysis(ir);
    patternDetection(ir);

    cout << "\n--- IR Analysis Completed ---\n";

    return 0;
}
