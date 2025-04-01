#include "QuineMcTable.h"
#include <iomanip>
#include <algorithm>

#include "../implicants_table/ImplicantsTable.h"

// Constructors
QuineMcTable::QuineMcTable() {
    log = new Logger;

    numberOfVariables = 0;
}

QuineMcTable::QuineMcTable(Logger* Log, vector<Term> Minterms,
                           int NumberOfVariables) {
    log = Log;

    minterms.assign(Minterms.begin(), Minterms.end());
    _minterms.assign(Minterms.begin(), Minterms.end());
    // Just for logging & debugging purposes
    numberOfVariables = NumberOfVariables;

    createTable();
    solve();

    _logData();
}

// Setters
void QuineMcTable::_setLogger(Logger* logger) {
    log = logger;
}

// Helpers
// Create table to track combinable minterms
void QuineMcTable::createTable() {
    table.resize(minterms.size(), vector<string>(minterms.size(), ""));

    for (int i = 0; i < minterms.size(); i++) {
        for (int j = i + 1; j < minterms.size(); j++) {
            if (minterms[i].canCombineWith(minterms[j])) {
                table[i][j] = "X";
            }
        }
    }
}

// solve: find prime implicants
void QuineMcTable::solve() {
    sortMintermsByOnes(); // sort before processing

    while (!minterms.empty()) {
        vector<Term> newMinterms = combineTerms();
        if (newMinterms.empty()) {
            break; // stop if no new terms created
        }
        minterms.assign(newMinterms.begin(), newMinterms.end());
    }

    // Setting Prime Implicants as string expressions
    set<string> primeImpsSet;

    vector<char> variables(numberOfVariables);
    for (int i = 0; i < numberOfVariables; i++) {
        variables[i] = static_cast<char>(65 + i);
    }

    for (int i = 0; i < primeImps.size(); i++) {
        primeImpsSet.insert(ImplicantsTable::getExpressionFromBinary(
            primeImps[i].getBinaryValue(),
            variables));
    }
    *log << endl;

    primeImpsString.assign(primeImpsSet.begin(), primeImpsSet.end());
}

void QuineMcTable::sortMintermsByOnes() {
    sort(minterms.begin(), minterms.end(), QuineMcTable::compareTerms);
}

// Sorting minterms by the number of 1s in binary representation
bool QuineMcTable::compareTerms(Term& a, Term& b) {
    return a.getOnesCount() < b.getOnesCount();
}

vector<Term> QuineMcTable::combineTerms() {
    vector<Term> newTerms;
    vector<bool> combined(minterms.size(), false);

    for (int i = 0; i < minterms.size(); i++) {
        for (int j = i + 1; j < minterms.size(); j++) {
            if (minterms[i].canCombineWith(minterms[j])) {
                Term combinedTerm = minterms[i].combineWith(&minterms[j]);
                if (find(newTerms.begin(), newTerms.end(), combinedTerm) ==
                    newTerms.end()) {
                    newTerms.push_back(combinedTerm);
                }
                combined[i] = true;
                combined[j] = true;
            }
        }
    }

    // Add terms that were not combined (prime implicants)
    for (int i = 0; i < minterms.size(); i++) {
        if (!combined[i]) {
            primeImps.push_back(minterms[i]);
        }
    }

    return newTerms;
}

// Methods
// Get prime implicants
vector<Term> QuineMcTable::getPrimeImplicants() {
    return primeImps;
}

vector<string> QuineMcTable::getPrimeImplicantsString() {
    return primeImpsString;
}

// Utils
void QuineMcTable::_logData() {
    *log << "[QuineMcTable] Prime Implicants: ";
    for (int i = 0; i < primeImps.size(); i++) {
        *log << primeImps[i].getBinaryValue();

        if (i < primeImps.size() - 1) {
            *log << " , ";
        }
    }
    *log << endl << endl;

    *log << "[QuineMcTable] Prime Implicants: ";
    for (int i = 0; i < primeImpsString.size(); i++) {
        *log << primeImpsString[i];

        if (i < primeImpsString.size() - 1) {
            *log << " , ";
        }
    }
    *log << endl << endl;
}
