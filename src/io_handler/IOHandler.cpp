#include "IOHandler.h"

#include <fstream>
#include <iostream>
using namespace std;

#include "../implicants_table/ImplicantsTable.h"
#include "../verilog_composer/VerilogComposer.h"
#include "../quine_mc_table/QuineMcTable.h"

// Constructors
IOHandler::IOHandler() {
    log = new Logger;

    numberOfVariables = 0;
};

IOHandler::IOHandler(Logger* Log, string InputFilepath) {
    log = Log;

    inputFilepath = move(InputFilepath);

    numberOfVariables = 0;
}

IOHandler::IOHandler(Logger* Log, string InputFilepath, string OutputFilepath) {
    log = Log;

    string inputFilepath = move(InputFilepath);
    string outputFilepath = move(OutputFilepath);

    numberOfVariables = 0;
    readInputFile();
}

IOHandler::IOHandler(Logger* Log, string InputFilepath, string OutputFilepath,
                     string VerilogFile) {
    log = Log;

    string inputFilepath = move(InputFilepath);
    string outputFilepath = move(OutputFilepath);
    string verilogFilepath = move(VerilogFile);

    numberOfVariables = 0;
    readInputFile();
}

IOHandler::IOHandler(Logger* Log, string InputFilepath, string OutputFilepath,
                     string VerilogFile, string LogFilepath) {
    log = Log;

    string inputFilepath = move(InputFilepath);
    string outputFilepath = move(OutputFilepath);
    string logFilepath = move(LogFilepath);
    string verilogFilepath = move(VerilogFile);

    numberOfVariables = 0;
    readInputFile();
}

// Helpers
void IOHandler::readInputFile() {
    ifstream inputFile(inputFilepath);
    if (!inputFile.is_open()) {
        cerr << "Error opening file " << inputFilepath << endl;
        exit(1);
    }

    // Read the number of variables
    inputFile >> numberOfVariables;

    // Read the minterms
    string line;
    inputFile >> line;
    stringstream ss(line);
    string term;

    while (getline(ss, term, ',')) {
        minterms.emplace_back(log, stoi(term.substr(1)), numberOfVariables);
    }

    // Read the don't-cares
    inputFile >> line;
    ss.seekp(0);

    while (getline(ss, term, ',')) {
        dontcares.emplace_back(log, stoi(term.substr(1)), numberOfVariables);
    }

    inputFile.close();
}

// Setters
void IOHandler::_setLogger(Logger* logger) {
    log = logger;
}

void IOHandler::setInputFilePath(string InputFilePath) {
    inputFilepath = move(InputFilePath);
    readInputFile();
}

// Methods
string IOHandler::resolveMinimizedExpression() {
    vector<Term> allTerms = minterms;
    allTerms.insert(allTerms.end(), dontcares.begin(), dontcares.end());

    QuineMcTable QMTable(log, allTerms, numberOfVariables);

    ImplicantsTable PImpsTable(log, QMTable.getPrimeImplicants(), minterms,
                               numberOfVariables);

    minimizedExpression = PImpsTable.getMinimizedExpression();
    return minimizedExpression;
}

bool IOHandler::writeToOutputFiles() {
    // Write to output file (if exists)
    if (!outputFilepath.empty()) {
        ofstream outputFile(outputFilepath);
        if (!outputFile.is_open()) {
            cerr << "Error writing to file " << outputFilepath << endl;
            return false;
        }

        ifstream inputFile(inputFilepath);
        if (!inputFile.is_open()) {
            cerr << "Error opening file " << inputFilepath << endl;
            return false;
        }

        stringstream fileContent;
        fileContent << inputFile.rdbuf();

        outputFile << fileContent.str() << endl;
        outputFile << minimizedExpression << endl;

        outputFile.close();
    }

    if (!verilogFilepath.empty()) {
        VerilogComposer vComposer(log, minimizedExpression);

        ofstream verilogFile(verilogFilepath);
        if (!verilogFile.is_open()) {
            cerr << "Error writing to file " << verilogFilepath << endl;
            return false;
        }

        verilogFile << vComposer.getVerilogCode();

        verilogFile.close();
    }

    if (!logFilepath.empty()) {
        ofstream logFile(logFilepath);
        if (!logFile.is_open()) {
            cerr << "Error writing to file " << logFilepath << endl;
            return false;
        }

        logFile << log->toString();
    }

    return true;
}
