#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, string> errorMap = {
    {"expected ';'", "MissingSemicolon"},
    {"not declared", "UndeclaredVariable"},
    {"division by zero", "DivisionByZero"}
};

string classify(string msg) {
    for(auto &e : errorMap) {
        if(msg.find(e.first) != string::npos)
            return e.second;
    }
    return "UnknownError";
}

void runTests() {

    vector<pair<string,string>> testCases = {
        {"expected ';' before return", "MissingSemicolon"},
        {"variable x not declared", "UndeclaredVariable"},
        {"division by zero", "DivisionByZero"},
        {"", "Invalid"},
        {"random error", "UnknownError"}
    };

    cout << "\n--- Running Test Cases ---\n";

    for(auto test : testCases) {

        string input = test.first;
        string expected = test.second;

        string output;

        if(input.empty()) {
            output = "Invalid";
        } else {
            output = classify(input);
        }

        cout << "\nInput: " << input;
        cout << "\nExpected: " << expected;
        cout << "\nOutput: " << output;

        if(output == expected)
            cout << "\nResult: PASS\n";
        else
            cout << "\nResult: FAIL\n";
    }
}

int main() {

    cout<<"Testing Module Started"<<endl;

    runTests();

    cout<<"\n--- Testing Completed ---\n";

    return 0;
}
