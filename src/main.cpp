#include <iostream>
#include <fstream>
using namespace std;

#include "io_handler/IOHandler.h"
#include "logger/Logger.h"

string usageMsg(const string& argv0) {
    return "Usage: " + argv0 + " [-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>";
}

int main(int argc, char* argv[]) {
    Logger log;
    bool verbose = false;
    string inputFilepath;
    string outputFilepath;
    string logFilepath;
    string verilogFilepath;

    // Handling Command Line Arguments
    if (argc < 2) {
        log.fatal("Error: please specify a valid input file\n\n" + usageMsg(argv[0]));
    }

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-v") {
            verbose = true;
        } else if (string(argv[i]) == "-d") {
            if (argv[i + 1] == nullptr || string(argv[i + 1]).
                starts_with("-")) {
                log.fatal("Error: Log file path must be provided after -d\n\n" + usageMsg(argv[0]));
            }

            logFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]) == "-o") {
            if (argv[i + 1] == nullptr || string(argv[i + 1]).
                starts_with("-")) {
                log.fatal("Error: Output file path must be provided after -o\n\n" + usageMsg(argv[0]));
            }

            outputFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]) == "--verilog") {
            if (argv[i + 1] == nullptr || string(argv[i + 1]).
                starts_with("-")) {
                log.fatal("Error: Output Verilog file path must be provided after --verilog\n\n" + usageMsg(argv[0]));
            }

            verilogFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]).starts_with("-")) {
            log.fatal("Error: Unknown flag: " + string(argv[i]) + " " + usageMsg(argv[0]));
        } else {
            inputFilepath = string(argv[i]);
            if (inputFilepath.empty()) {
                log.fatal("Error: Input file name must be provided" + usageMsg(argv[0]));
            }
        }
    }

    if (verbose) {
        log = Logger(&cout);
    }

    // Reading, Processing Business Logic, and Writing to output destinations are handed to IOHandler
    IOHandler ioHandler(&log, inputFilepath, outputFilepath, verilogFilepath,
                        logFilepath);
    cout << "F = " << ioHandler.resolveMinimizedExpression() << endl;

    if (!ioHandler.writeToOutputFiles()) {
        log.fatal("Error: Failed to write to output files!");
    }

    return 0;
}
