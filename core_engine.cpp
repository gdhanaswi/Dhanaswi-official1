#include <iostream>
#include <string>
#include <map>
using namespace std;

// Error classification
string classifyError(string errorMsg) {
    if (errorMsg.find("expected ';'") != string::npos)
        return "MissingSemicolon";

    if (errorMsg.find("not declared") != string::npos)
        return "UndeclaredVariable";

    if (errorMsg.find("division by zero") != string::npos)
        return "DivisionByZero";

    return "UnknownError";
}

// Explanation generator
void generateExplanation(string errorType) {
    if (errorType == "MissingSemicolon") {
        cout << "\nExplanation: You forgot to add a semicolon at the end of the statement.\n";
        cout << "Suggested Fix: Add ';' at the end of the line.\n";
        cout << "Security Note: Syntax errors may hide logical bugs.\n";
    }
    else if (errorType == "UndeclaredVariable") {
        cout << "\nExplanation: You are using a variable before declaring it.\n";
        cout << "Suggested Fix: Declare the variable with proper type.\n";
        cout << "Security Note: Undeclared variables may cause undefined behavior.\n";
    }
    else if (errorType == "DivisionByZero") {
        cout << "\nExplanation: Division by zero is not allowed.\n";
        cout << "Suggested Fix: Ensure denominator is not zero before division.\n";
        cout << "Security Note: Can cause runtime crash.\n";
    }
    else {
        cout << "\nExplanation: Unknown error type.\n";
    }
}

int main() {
    string compilerError;

    cout << "Enter compiler error message:\n";
    getline(cin, compilerError);

    cout << "\n--- CORE ENGINE LOG ---\n";

    // Pass 1: Classification
    string errorType = classifyError(compilerError);
    cout << "Error Classified As: " << errorType << endl;

    // Pass 2 & 3: Transformation
    generateExplanation(errorType);

    cout << "\n--- END OF ANALYSIS ---\n";

    return 0;
}
