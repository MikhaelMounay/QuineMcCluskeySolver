#include "VerilogComposer.h"

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
using namespace std;

// Constructors
VerilogComposer::VerilogComposer() {
    log = new Logger;
    boolExpression = "";
    verilogCode = "";
}

VerilogComposer::VerilogComposer(string BoolExpression) {
    log = new Logger;
    boolExpression = BoolExpression;
    verilogCode = "";

    generateVerilog();
}

// Helpers
void VerilogComposer::generateVerilog() {
    vector<string> subExpressions = processExpression();
    ostringstream oss;

    oss << "`timescale 1ns / 1ps\n\n";
    oss << "// Boolean Expression: " << boolExpression << "\n\n";

    // Module Declaration
    oss << "module fn(\n\tinput ";
    unordered_map<char, bool> chars;
    for (int i = 0; i < boolExpression.length(); i++) {
        if (chars[boolExpression[i]] || !isalpha(boolExpression[i])) {
            continue;
        }

        chars[boolExpression[i]] = true;
    }

    vector<char> sortedChars;
    for (auto it = chars.begin(); it != chars.end(); it++) {
        if (it->second) {
            sortedChars.push_back(it->first);
        }
    }

    sort(sortedChars.begin(), sortedChars.end());
    for (int i = 0; i < sortedChars.size(); i++) {
        oss << sortedChars[i] << ", ";
    }

    oss << "\n\toutput X\n\t);\n\n";

    // Wires Declaration
    oss << "\twire ";
    for (int i = 0; i < subExpressions.size(); i++) {
        oss << "_" << i + 1;

        if (i < subExpressions.size() - 1) {
            oss << ", ";
        }
    }
    oss << ";\n\n";

    // (and) primitives
    for (int i = 0; i < subExpressions.size(); i++) {
        oss << "\tand(_" << i + 1 << ", ";
        for (int j = 0; j < subExpressions[i].length(); j++) {
            if (j + 1 < subExpressions[i].length() && subExpressions[i][j + 1]
                == '\'') {
                oss << "~" << subExpressions[i][j];
                j++;
            } else {
                oss << subExpressions[i][j];
            }

            if (j < subExpressions[i].length() - 1) {
                oss << ", ";
            }
        }
        oss << ");\n";
    }
    oss << "\n";

    // (or) primitives
    oss << "\tor(X, ";
    for (int i = 0; i < subExpressions.size(); i++) {
        oss << "_" << i + 1;

        if (i < subExpressions.size() - 1) {
            oss << ", ";
        }
    }

    // endmodule
    oss << ");\n\nendmodule\n";

    verilogCode = oss.str();
}

vector<string> VerilogComposer::processExpression() {
    string expression = boolExpression;
    expression.erase(remove(expression.begin(), expression.end(), ' '),
                     expression.end());

    vector<string> subExpressions;
    stringstream ss;
    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == '+') {
            subExpressions.push_back(ss.str());
            ss.seekp(0);
        } else {
            ss << expression[i];
        }
    }
    subExpressions.push_back(ss.str());

    return subExpressions;
}

// Getters
string VerilogComposer::getVerilogCode() {
    return verilogCode;
}

// Setters
void VerilogComposer::_setLogger(Logger* logger) {
    delete log;
    log = logger;
}

// Methods
bool VerilogComposer::saveToFile(string filepath) {
    if (verilogCode.empty() || filepath.empty()) {
        return false;
    }

    ofstream file(filepath);
    if (!file.is_open()) {
        return false;
    }

    file << verilogCode;
    file.close();

    return true;
}
