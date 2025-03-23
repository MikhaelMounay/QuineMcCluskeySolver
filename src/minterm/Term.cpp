#include "Term.h"

// Constructor
Term::Term(int DecimalValue, int numOfVariables) {
    decimalValue = DecimalValue;
    binaryValue = convertDecToBin(numOfVariables);
    onesCount = calculateOnesCount();
    combined = false;
    coveredTerms = {};
}

Term::Term(string BinaryValue, set<int> CoveredTerms) {
    binaryValue = BinaryValue;
    onesCount = calculateOnesCount();
    combined = false;
    coveredTerms = move(CoveredTerms);
}

// Helpers
string Term::convertDecToBin(int numOfVariables) {
    // TODO: convert (int) decimalValue to (string) binaryValue and store it in binaryValue
    return "";
}

int Term::calculateOnesCount() {
    // TODO: calculate the number of 1's in the binaryValue
    return 0;
}

// Getters
string Term::getBinaryValue() {
    return binaryValue;
}

bool Term::isCombined() {
    return combined;
}

// Setters
void Term::setCombined(bool val) {
    combined = val;
}

// Methods

bool Term::canCombineWith(const Term& term) {
    // TODO: check if two terms can be combined
}

Term Term::combineWith(const Term& otherTerm) {
    // TODO: combine two terms together and return the combined one
}
