#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* ==============================
   Training Dataset
   ============================== */

struct TrainingSample {
    string errorMessage;
    string label;
};

vector<TrainingSample> dataset = {
    {"expected ';' before 'return'", "MissingSemicolon"},
    {"expected ';' after expression", "MissingSemicolon"},
    {"was not declared in this scope", "UndeclaredVariable"},
    {"division by zero", "DivisionByZero"},
    {"expected ')' before ';'", "MissingBracket"}
};

/* ==============================
   AI Pattern Matching
   ============================== */

string predictErrorType(string error) {

    for (auto sample : dataset) {

        if (error.find(sample.errorMessage) != string::npos)
            return sample.label;
    }

    if (error.find("not declared") != string::npos)
        return "UndeclaredVariable";

    if (error.find("expected ';'") != string::npos)
        return "MissingSemicolon";

    return "UnknownError";
}

/* ==============================
   Explanation Generator
   ============================== */

void generateExplanation(string type) {

    cout << "\n--- AI Generated Explanation ---\n";

    if (type == "MissingSemicolon") {
        cout << "You forgot to add a semicolon at the end of the statement.\n";
        cout << "Fix: Add ';' after the statement.\n";
    }
    else if (type == "UndeclaredVariable") {
        cout << "A variable is used without declaration.\n";
        cout << "Fix: Declare the variable before using it.\n";
    }
    else if (type == "DivisionByZero") {
        cout << "Division by zero causes runtime error.\n";
        cout << "Fix: Ensure denominator is not zero.\n";
    }
    else if (type == "MissingBracket") {
        cout << "A closing parenthesis is missing.\n";
        cout << "Fix: Add ')' at the correct position.\n";
    }
    else {
        cout << "Unknown compiler error.\n";
    }
}

/* ==============================
   Evaluation Metrics
   ============================== */

void evaluateModel() {

    vector<string> testErrors = {
        "expected ';' before 'return'",
        "variable x was not declared in this scope",
        "division by zero"
    };

    vector<string> expectedLabels = {
        "MissingSemicolon",
        "UndeclaredVariable",
        "DivisionByZero"
    };

    int correct = 0;

    for (int i = 0; i < testErrors.size(); i++) {

        string prediction = predictErrorType(testErrors[i]);

        if (prediction == expectedLabels[i])
            correct++;
    }

    double accuracy = (double)correct / testErrors.size();

    cout << "\n--- Model Evaluation ---\n";
    cout << "Accuracy: " << accuracy * 100 << "%\n";
}

/* ==============================
   MAIN FUNCTION
   ============================== */

int main() {

    cout << "AI-Based Compiler Error Analyzer\n";

    string errorMessage;

    cout << "\nEnter compiler error message:\n";
    getline(cin, errorMessage);

    string predictedType = predictErrorType(errorMessage);

    cout << "\nPredicted Error Type: " << predictedType << endl;

    generateExplanation(predictedType);

    evaluateModel();

    return 0;
}
