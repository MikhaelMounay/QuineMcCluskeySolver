#ifndef TERM_H
#define TERM_H

#include <string>
#include <set>
using namespace std;

#include "../logger/Logger.h"

class Term {
private:
    Logger* log;

    int decimalValue;
    string binaryValue;
    int onesCount;
    bool combined;
    set<int> coveredTerms;

    // Helpers
    string convertDecToBin(int numOfVariables);
    int calculateOnesCount();

public:
    // Constructor
    Term();
    Term(int DecimalValue, int numOfVariables);
    Term(string BinaryValue, set<int> CoveredTerms);

    // Getters
    string getBinaryValue();
    bool isCombined();

    // Setters
    void _setLogger(Logger* logger);
    void setCombined(bool val);

    // Methods
    bool canCombineWith(const Term& term);
    Term combineWith(Term* otherTerm);
};

#endif //TERM_H
