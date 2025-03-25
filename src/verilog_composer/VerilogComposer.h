#ifndef VERILOGCOMPOSER_H
#define VERILOGCOMPOSER_H

#include "../logger/Logger.h"

class VerilogComposer {
private:
    Logger* log;
    string boolExpression;

public:
    // Constructors
    VerilogComposer();
    VerilogComposer(string BoolExpression);

    // Setters
    void _setLogger(Logger* logger);

    // Methods
    bool saveToFile(string filepath);
};

#endif //VERILOGCOMPOSER_H
