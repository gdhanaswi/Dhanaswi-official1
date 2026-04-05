#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* Structure to store training data */
struct TrainingData
{
    string errorMessage;
    string label;
};

/* Training dataset */
vector<TrainingData> trainingSet;

/* Function to train the model */
void trainModel()
{
    trainingSet.push_back({"expected ';' before 'return'", "MissingSemicolon"});
    trainingSet.push_back({"expected ';' after expression", "MissingSemicolon"});
    trainingSet.push_back({"was not declared in this scope", "UndeclaredVariable"});
    trainingSet.push_back({"division by zero", "DivisionByZero"});
    trainingSet.push_back({"expected ')' before ';'", "MissingBracket"});

    cout<<"AI Model Training Completed"<<endl;
}

/* Prediction function */
string predictError(string inputError)
{
    for(auto data : trainingSet)
    {
        if(inputError.find(data.errorMessage) != string::npos)
        {
            return data.label;
        }
    }

    if(inputError.find("not declared") != string::npos)
        return "UndeclaredVariable";

    if(inputError.find("expected ';'") != string::npos)
        return "MissingSemicolon";

    return "UnknownError";
}

/* Explanation generator */
void explainError(string type)
{
    cout<<"\nExplanation:"<<endl;

    if(type=="MissingSemicolon")
        cout<<"A semicolon is missing at the end of the statement."<<endl;

    else if(type=="UndeclaredVariable")
        cout<<"A variable is used before it is declared."<<endl;

    else if(type=="DivisionByZero")
        cout<<"Division by zero causes runtime errors."<<endl;

    else if(type=="MissingBracket")
        cout<<"A closing parenthesis is missing in the expression."<<endl;

    else
        cout<<"Unknown compiler error."<<endl;
}

/* Main Function */
int main()
{
    trainModel();

    string errorMsg;

    cout<<"\nEnter compiler error message:"<<endl;
    getline(cin,errorMsg);

    string prediction = predictError(errorMsg);

    cout<<"\nPredicted Error Type: "<<prediction<<endl;

    explainError(prediction);

    return 0;
}
