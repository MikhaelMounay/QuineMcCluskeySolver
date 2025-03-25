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

Term::Term(int DecimalValue, int numOfVariables) {
    log = new Logger;

    decimalValue = DecimalValue;
    binaryValue = convertDecToBin(numOfVariables);
    onesCount = getOnesCount();
    combined = false;
    coveredTerms = {DecimalValue}; // The term covers itself initially

}

Term::Term(string BinaryValue, set<int> CoveredTerms) {
    log = new Logger;

    decimalValue = -1;
    binaryValue = move(BinaryValue);
    onesCount = getOnesCount();
    combined = false;
    coveredTerms = move(CoveredTerms);
}

// Helpers
string Term::convertDecToBin(int numOfVariables) {
    // Convert to 20-bit binary (the max number of variables our program can handle)
    string binaryStr = bitset<20>(decimalValue).to_string();
    // Extract only relevant bits according to the processed function
    return binaryStr.substr(20 - numOfVariables);
    *log<<"decimal value:"<< decimalValue<<"binary value:"<<binaryValue<<endl;
}

int Term::getOnesCount() {
    return count(binaryValue.begin(), binaryValue.end(), '1');
    *log<<"Ones count"<< count(binaryValue.begin(), binaryValue.end(), '1');;
}

// Getters
int Term::getDecimalValue() {
    return decimalValue;
    *log<<" get decimal value"<<decimalValue<<endl;
}

string Term::getBinaryValue() {
    return binaryValue;
    *log<<"get binary value"<<binaryValue<<endl;
}

bool Term::isCombined() {
    return combined;
    *log<<"is combined "<<combined<<endl;
}

// TODO: test suite
set<int> Term::getCoveredTerms() {
    return coveredTerms;
    *log<<"get covered terms:"<<coveredTerms;
}

// Setters
void Term::_setLogger(Logger* logger) {
    log = logger;
    *log<<"set logger";
}

void Term::setCombined(bool val) {
    combined = val;
    *log<<"set combined";
}

// Methods
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

Term Term::combineWith(Term* otherTerm) {
    if (!canCombineWith(*otherTerm)) {
        return Term{};
    }

    // Replace differing bit with '-'
    string combinedBinary = binaryValue;
    for (int i = 0; i < binaryValue.length(); i++) {
        if (binaryValue[i] != otherTerm->binaryValue[i]) {
            combinedBinary[i] = '-';
        }
    }

    // Add the covered terms for both terms together
    set<int> newCoveredTerms = coveredTerms;
    newCoveredTerms.insert(otherTerm->coveredTerms.begin(),
                           otherTerm->coveredTerms.end());

    combined = true;
    otherTerm->setCombined(true);

    return Term{combinedBinary, newCoveredTerms};
}

// TODO: test suite
bool Term::covers(Term& otherTerm) {
    return coveredTerms.contains(otherTerm.getDecimalValue());
}

// Operator Overloading
bool Term::operator==(const Term& other) {
    return binaryValue == other.binaryValue;
}
