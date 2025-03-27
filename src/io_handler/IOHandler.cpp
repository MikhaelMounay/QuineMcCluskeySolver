#include "IOHandler.h"

#include <fstream>
#include<algorithm>
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
    readInputFile();
}

IOHandler::IOHandler(Logger* Log, string InputFilepath, string OutputFilepath) {
    log = Log;

    inputFilepath = move(InputFilepath);
    outputFilepath = move(OutputFilepath);

    numberOfVariables = 0;
    readInputFile();
}

IOHandler::IOHandler(Logger* Log, string InputFilepath, string OutputFilepath,
                     string VerilogFile) {
    log = Log;

    inputFilepath = move(InputFilepath);
    outputFilepath = move(OutputFilepath);
    verilogFilepath = move(VerilogFile);

    numberOfVariables = 0;
    readInputFile();
}

IOHandler::IOHandler(Logger* Log, string InputFilepath, string OutputFilepath,
                     string VerilogFile, string LogFilepath) {
    log = Log;

    inputFilepath = move(InputFilepath);
    outputFilepath = move(OutputFilepath);
    logFilepath = move(LogFilepath);
    verilogFilepath = move(VerilogFile);

    numberOfVariables = 0;
    readInputFile();
}

// Helpers
void IOHandler::readInputFile() {
    ifstream inputFile(inputFilepath);
    if (!inputFile.is_open()) {
        log->fatal("Error opening file " + inputFilepath);
    }

    if (inputFile.peek() == ifstream::traits_type::eof()) {
        log->fatal("File " + inputFilepath + " is empty");
    }

    // Read the number of variables
    inputFile >> numberOfVariables;

    // Validation on numberOfVariables
    if (numberOfVariables == 0) {
        log->fatal("Error: please provide the number of variables");
    }
    if (numberOfVariables > 20) {
        log->fatal("Error: max supported number of variables is 20");
    }
    inputFile.get(); // To skip the '\n' after

    // Read the minterms
    string line;
    getline(inputFile, line);

    // Validation on numberOfVariables
    if (line.empty() || line == "m") {
        log->fatal("Error: please provide a valid input for minterms");
    }

    stringstream ss(line);
    string term;
    while (getline(ss, term, ',')) {
        minterms.emplace_back(log, stoi(term.substr(1)), numberOfVariables);
    }

    // Read the don't-cares
    getline(inputFile, line);
    ss.str(line);

    if (!line.empty() && line != "d") {
        ss.seekg(0);
        ss.clear();

        while (getline(ss, term, ',')) {
            Term tempTerm(log, stoi(term.substr(1)), numberOfVariables);
            if (find(minterms.begin(), minterms.end(), tempTerm) == minterms.end()) {
                dontcares.emplace_back(log, stoi(term.substr(1)), numberOfVariables);
            } else {
                log->fatal("Error: " + term.substr(1) + " cannot be a minterm and a don't-care term at the same time. i.e., minterms and don't cares shouldn't overlap!");
            }
        }
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
            log->fatal("Error writing to file " + outputFilepath);
            return false;
        }

        ifstream inputFile(inputFilepath);
        if (!inputFile.is_open()) {
            log->fatal("Error opening file " + inputFilepath);
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
            log->fatal("Error writing to file " + verilogFilepath);
            return false;
        }

        verilogFile << vComposer.getVerilogCode();

        verilogFile.close();
    }

    if (!logFilepath.empty()) {
        ofstream logFile(logFilepath);
        if (!logFile.is_open()) {
            log->fatal("Error writing to file " + logFilepath);
            return false;
        }

        logFile << log->toString();
    }

    return true;
}
