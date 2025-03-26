#include <iostream>
#include <fstream>
using namespace std;

#include "logger/Logger.h"

int main(int argc, char* argv[]) {
    Logger log;
    bool verbose = false;
    string inputFilepath;
    string outputFilepath;
    string logFilepath;
    string verilogFilepath;

    // Handling Command Line Arguments
    if (argc < 2) {
        cerr << "Usage: " << argv[0] <<
            "[-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>"
            <<
            endl;
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-v") {
            verbose = true;
        } else if (string(argv[i]) == "-d") {
            if (string(argv[i + 1]).empty() || string(argv[i + 1]).starts_with("-")) {
                cerr << "Error: Log file path must be provided after -d" <<
                    endl;
                cout << "Usage: " << argv[0] <<
                    "[-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>"
                    <<
                    endl;
                return 1;
            }

            logFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]) == "-o") {
            if (string(argv[i + 1]).empty() || string(argv[i + 1]).starts_with("-")) {
                cerr << "Error: Output file path must be provided after -o" <<
                    endl;
                cout << "Usage: " << argv[0] <<
                    "[-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>"
                    <<
                    endl;
                return 1;
            }

            outputFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]) == "--verilog") {
            if (string(argv[i + 1]).empty() || string(argv[i + 1]).starts_with("-")) {
                cerr << "Error: Output Verilog file path must be provided after --verilog" <<
                    endl;
                cout << "Usage: " << argv[0] <<
                    "[-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>"
                    <<
                    endl;
                return 1;
            }

            verilogFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]).starts_with("-")) {
            cerr << "Error: Unknown flag: " << string(argv[i]) << endl;
            cout << "Usage: " << argv[0] <<
                    "[-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>"
                    <<
                    endl;
            return 1;
        } else {
            inputFilepath = string(argv[i]);
            if (inputFilepath.empty()) {
                cerr << "Error: Input file name must be provided" << endl;
                return 1;
            }
        }
    }

    if (verbose) {
        log = Logger(&cout);
    }

    log << "Hello, World!\n";
    // Read input file

    // Output to console

    // Output to _minimized.txt file

    // Output Verilog to .v file

    // Write log to dump file
    if (!outputFilepath.empty()) {
        ofstream logFile(outputFilepath);
        if (!logFile.is_open()) {
            cerr << "Error: Could not open log file " << outputFilepath << endl;
            return 1;
        }
        logFile << log.toString();
        logFile.close();
    }

    return 0;
}
