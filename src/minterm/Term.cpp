#include "Term.h"
#include <bitset>
#include <algorithm> // Fix for count()
#include <iostream>

// Constructor
Term::Term(int DecimalValue, int numOfVariables) {
    decimalValue = DecimalValue;
    binaryValue = convertDecToBin(numOfVariables);
    onesCount = calculateOnesCount();
    combined = false;
    coveredTerms = {DecimalValue}; // The term covers itself initially
}

Term::Term(string BinaryValue, set<int> CoveredTerms) {
    binaryValue = BinaryValue;
    onesCount = calculateOnesCount();
    combined = false;
    coveredTerms = move(CoveredTerms);
}

// Helpers
string Term::convertDecToBin(int numOfVariables) {
    string binaryStr = bitset<32>(decimalValue).to_string(); // Convert to 32-bit binary
    return binaryStr.substr(32 - numOfVariables); // Extract only relevant bits
}

int Term::calculateOnesCount() {
    return std::count(binaryValue.begin(), binaryValue.end(), '1'); // Use std::count correctly
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
    int diffCount = 0;
    for (size_t i = 0; i < binaryValue.length(); i++) {
        if (binaryValue[i] != term.binaryValue[i]) {
            diffCount++;
            if (diffCount > 1) return false; // Must differ by only one bit
        }
    }
    return (diffCount == 1);
}

Term Term::combineWith(const Term& otherTerm) {
    string combinedBinary = binaryValue;
    for (size_t i = 0; i < binaryValue.length(); i++) {
        if (binaryValue[i] != otherTerm.binaryValue[i]) {
            combinedBinary[i] = '-'; // Replace differing bit with '-'
        }
    }
    set<int> newCoveredTerms = coveredTerms;
    newCoveredTerms.insert(otherTerm.coveredTerms.begin(), otherTerm.coveredTerms.end());

    return Term(combinedBinary, newCoveredTerms);
}
