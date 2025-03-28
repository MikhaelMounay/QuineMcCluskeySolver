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
    vector<Term> maxterms;
    vector<Term> dontcares;
    int numberOfVariables;
    string minimizedExpression;
    string verilogCode;

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

    // Setters
    void _setLogger(Logger* logger);
    void setInputFilePath(string InputFilePath);

    // Methods
    string resolveMinimizedExpression();
    bool writeToOutputFiles();
};

#endif //IOHANDLER_H
