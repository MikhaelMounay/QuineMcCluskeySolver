#ifndef VERILOGCOMPOSER_H
#define VERILOGCOMPOSER_H

#include <vector>
#include "../logger/Logger.h"

class VerilogComposer {
private:
    Logger* log;
    string boolExpression;
    string verilogCode;

    // Helpers
    void generateVerilog();
    vector<string> processExpression();

public:
    // Constructors
    VerilogComposer();
    VerilogComposer(Logger* Log, string BoolExpression);

    // Getters
    string getVerilogCode();

    // Setters
    void _setLogger(Logger* logger);
};

#endif //VERILOGCOMPOSER_H
