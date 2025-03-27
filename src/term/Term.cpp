#include "Term.h"
#include <bitset>
#include <algorithm>
#include <utility>

// Constructor
Term::Term() {
    log = new Logger;

    decimalValue = -1;
    binaryValue = "";
    onesCount = -1;
    combined = false;

    coveredTerms = {};
}

Term::Term(Logger* Log, int DecimalValue, int numOfVariables) {
    log = Log;

    decimalValue = DecimalValue;
    binaryValue = convertDecToBin(numOfVariables);
    onesCount = getOnesCount();
    combined = false;
    coveredTerms = {DecimalValue};

    _logData();
}

Term::Term(Logger* Log, string BinaryValue, set<int> CoveredTerms) {
    log = Log;

    decimalValue = -1;
    binaryValue = move(BinaryValue);
    onesCount = getOnesCount();
    combined = false;
    coveredTerms = move(CoveredTerms);

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
set<int> Term::getCoveredTerms() {
    return coveredTerms;
}

// Setters
void Term::_setLogger(Logger* logger) {
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
    int diffCount = 0;

    for (int i = 0; i < binaryValue.length(); i++) {
        if (binaryValue[i] != term.binaryValue[i]) {
            diffCount++;
            if (diffCount > 1) {
                return false;
            }
        }
    }
    return (diffCount == 1);
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

    return Term{combinedBinary, newCoveredTerms};
}

// Checks if this term covers another term (based on decimal values)
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
