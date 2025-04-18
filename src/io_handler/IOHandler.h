#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <string>
#include <vector>
using namespace std;

#include "../term/Term.h"

class IOHandler {
private:
    Logger* log;

    string inputFilepath;
    string outputFilepath;
    string logFilepath;
    string verilogFilepath;

    vector<Term> minterms;
    vector<Term> dontcares;
    int numberOfVariables;
    vector<string> possibleMinimizedExpression;
    string verilogCode;

    vector<Term> primeImplicants;
    vector<string> primeImplicantsString;
    vector<Term> essentialImplicants;
    vector<string> essentialImplicantsString;

    // Helpers
    void readInputFile();

public:
    // Constructors
    IOHandler();
    explicit IOHandler(Logger* Log, string InputFilepath);
    IOHandler(Logger* Log, string InputFilepath, string OutputFilepath);
    IOHandler(Logger* Log, string InputFilepath, string OutputFilepath,
              string VerilogFile);
    IOHandler(Logger* Log, string InputFilepath, string OutputFilepath,
              string VerilogFile, string LogFilepath);

    // Getters
    int getNumberOfVariables();
    vector<Term> getPrimeImplicants();
    vector<string> getPrimeImplicantsString();
    vector<Term> getEssentialImplicants();
    vector<string> getEssentialsImplicantsString();

    // Setters
    void _setLogger(Logger* logger);
    void setInputFilePath(string InputFilePath);

    // Methods
    vector<string> resolveMinimizedExpression();
    string getStandardOutput();
    bool writeToOutputFiles();
};

#endif //IOHANDLER_H
