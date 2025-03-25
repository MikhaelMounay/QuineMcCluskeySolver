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


public:
    // Constructor
    Term();
    Term(int DecimalValue, int numOfVariables);
    Term(string BinaryValue, set<int> CoveredTerms);

    // Getters
    int getDecimalValue();
    string getBinaryValue();
    bool isCombined();
    set<int> getCoveredTerms();

    // Setters
    void _setLogger(Logger* logger);
    void setCombined(bool val);

    // Methods
    bool canCombineWith(const Term& term);
    Term combineWith(Term* otherTerm);
    bool covers(Term& term);
    int calculateOnesCount();
};

#endif //TERM_H
