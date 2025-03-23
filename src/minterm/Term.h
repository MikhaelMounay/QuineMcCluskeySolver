#ifndef MINTERM_H
#define MINTERM_H

#include <string>
#include <set>
using namespace std;

class Term {
private:
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
    Term(int DecimalValue, int numOfVariables);
    Term(string BinaryValue, set<int> CoveredTerms);

    // Getters
    string getBinaryValue();
    bool isCombined();

    // Setters
    void setCombined(bool val);

    // Methods
    bool canCombineWith(const Term &term);
    Term combineWith(const Term &otherTerm);
};

#endif //MINTERM_H
