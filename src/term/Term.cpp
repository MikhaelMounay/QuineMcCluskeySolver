#include "Term.h"
#include <bitset>
#include <algorithm>
#include <utility>

// Constructor
Term::Term() {
    log = new Logger;// Allocate a new Logger instance

    decimalValue = -1; // Default invalid decimal value
    binaryValue = ""; // Empty binary representation
    onesCount = -1;  // Invalid count of 1s (uninitialized state)
    combined = false; // Indicates this term has not been combined yet

    coveredTerms = {}; // No terms covered initially
}

Term::Term(int DecimalValue, int numOfVariables) {
    log = new Logger();  // Allocate a new Logger instance

    decimalValue = DecimalValue; // Store the given decimal value
    binaryValue = convertDecToBin(numOfVariables);  // Convert to binary representation
    onesCount = getOnesCount();// Count the number of ones ('1') in the binary value
    combined = false; // Initially, this term has not been combined with another
    coveredTerms = {DecimalValue}; // The term covers itself initially

    _logData();
}

Term::Term(string BinaryValue, set<int> CoveredTerms) {
    log = new Logger; // Allocate a new Logger instance

    decimalValue = -1;  // No specific decimal value associated
    binaryValue = move(BinaryValue); // Move the binary string into the member variable
    onesCount = getOnesCount();// Count the number of ones ('1') in the binary value
    combined = false;// Initially, this term has not been combined
    coveredTerms = move(CoveredTerms); // Move the covered terms set

    _logData();
}
// Helpers

// Converts the decimal value to a binary string with a fixed number of bits
string Term::convertDecToBin(int numOfVariables) {
    // Convert to a 20-bit binary string (max number of variables supported)
    string binaryStr = bitset<20>(decimalValue).to_string();
    // Extract only the required number of bits for the given number of variables
    return binaryStr.substr(20 - numOfVariables);
}

// Counts the number of '1's in the binary representation
int Term::getOnesCount() {
    return count(binaryValue.begin(), binaryValue.end(), '1');
}

// Getters
// Returns the decimal representation of the term
int Term::getDecimalValue() {
    return decimalValue;
}
// Returns the binary representation of the term
string Term::getBinaryValue() {
    return binaryValue;
}
// Returns whether this term has been combined with another term
bool Term::isCombined() {
    return combined;
}
// Returns the set of terms that this term represents
// TODO: test suite
set<int> Term::getCoveredTerms() {
    return coveredTerms;
}

// Setters

// Assigns a new logger instance to the term
void Term::_setLogger(Logger* logger) {
    delete log;
    log = logger;
}
// Sets the combined flag
void Term::setCombined(bool val) {
    combined = val;
}

// Methods
// Checks if two terms can be combined (i.e., they differ by exactly one bit)
bool Term::canCombineWith(const Term& term) {
    // Check if they differ only by 1 bit
    int diffCount = 0; // Counter for differing bits
    // Iterate over the binary string and count differences
    for (int i = 0; i < binaryValue.length(); i++) {
        if (binaryValue[i] != term.binaryValue[i]) {
            diffCount++;
            if (diffCount > 1) { // If more than one difference, cannot combine
                return false;
            }
        }
    }
    return (diffCount == 1); // Valid combination if exactly one bit differs
}
// Combines this term with another term if possible
Term Term::combineWith(Term* otherTerm) {
    // Ensure the two terms are combinable
    if (!canCombineWith(*otherTerm)) {
        return Term{}; // Return an empty Term object if they cannot be combined
    }

    // Create a new binary string with differing bits replaced by '-'
    string combinedBinary = binaryValue;
    for (int i = 0; i < binaryValue.length(); i++) {
        if (binaryValue[i] != otherTerm->binaryValue[i]) {
            combinedBinary[i] = '-';
        }
    }

    // Merge the covered terms from both terms
    set<int> newCoveredTerms = coveredTerms;
    newCoveredTerms.insert(otherTerm->coveredTerms.begin(),
                           otherTerm->coveredTerms.end());
    // Mark both terms as combined
    combined = true;
    otherTerm->setCombined(true);
    // Return the new combined term
    return Term{combinedBinary, newCoveredTerms};
}
// Checks if this term covers another term (based on decimal values)
// TODO: test suite
bool Term::covers(Term& otherTerm) {
    return coveredTerms.contains(otherTerm.getDecimalValue());
}
// Operator Overloading

// Overloaded equality operator: Two terms are equal if they have the same binary value
bool Term::operator==(const Term& other) {
    return binaryValue == other.binaryValue;
}

// Utils

// Logs the details of the term
void Term::_logData() {
    *log << "[Term] Decimal value: " << decimalValue << " | Binary value: " <<
        binaryValue
        << " | OnesCount: " << onesCount << " | isCombined : " << isCombined <<
        endl;
    *log << "  coveredTerms : ";
    for (auto it = coveredTerms.begin(); it != coveredTerms.end(); it++) {
        *log << *it << " ";
    }
    *log << endl << endl;
}
