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

    // Utils
    void _logData();

public:
    // Constructor
    Term();
    Term(Logger* Log, int DecimalValue, int numOfVariables);
    Term(Logger* Log, string BinaryValue, set<int> CoveredTerms);

    // Getters
    int getDecimalValue();
    string getBinaryValue();
    bool isCombined();
    set<int> getCoveredTerms();

    // Setters
    void _setLogger(Logger* logger);
    void setCombined(bool val);

    // Methods
    int getOnesCount();
    bool canCombineWith(const Term& term);
    Term combineWith(Term* otherTerm);
    bool covers(Term& term);

    // Operator Overloading
    bool operator==(const Term& other);
};

#endif //TERM_H
