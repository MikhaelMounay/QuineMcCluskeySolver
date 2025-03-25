#include "QuineMcTable.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// constructor
QuineMcTable::QuineMcTable() {
    log = nullptr;
    numberOfVariables = 0;
}

QuineMcTable::QuineMcTable(vector<Term> Minterms, int NumberOfVariables) {
    minterms.assign(Minterms.begin(), Minterms.end());
    numberOfVariables = NumberOfVariables;
    log = nullptr;
    createTable(); // create the table
    solve();
}

// set Logger
void QuineMcTable::_setLogger(Logger* logger) {
    log = logger;
}

// create table to track combinable minterms
void QuineMcTable::createTable() {
    table.resize(minterms.size(), vector<string>(minterms.size(), ""));
    for (int i = 0; i < minterms.size(); i++)
    {
        for (int j = i + 1; j < minterms.size(); j++)
        {
            if (minterms[i].canCombineWith(minterms[j]))
            {
                table[i][j] = "X";
            }
        }
    }
}

// sorting minterms by the number of 1s in binary representation
bool compareTerms( Term& a,  Term& b) {
    return a.calculateOnesCount() < b.calculateOnesCount();
}

void QuineMcTable::sortMintermsByOnes() {
    sort(minterms.begin(), minterms.end(), compareTerms);
}

// combine terms
vector<Term> QuineMcTable::combineTerms() {
    vector<Term> newTerms;
    vector<bool> combined(minterms.size(), false);

    for (int i = 0; i < minterms.size(); i++)
    {
        for (int j = i + 1; j < minterms.size(); j++)
        {
            if (minterms[i].canCombineWith(minterms[j]))
            {
                Term combinedTerm = minterms[i].combineWith(&minterms[j]);
                if (find(newTerms.begin(), newTerms.end(), combinedTerm) == newTerms.end())
                {
                    newTerms.push_back(combinedTerm);
                }
                combined[i] = true;
                combined[j] = true;
            }
        }
    }

    // add terms that were not combined (prime implicants)
    for (int i = 0; i < minterms.size(); i++)
    {
        if (!combined[i])
        {
            primeImps.push_back(minterms[i]);
        }
    }

    return newTerms;
}

// solve: find prime implicants
void QuineMcTable::solve() {
    sortMintermsByOnes(); // sort before processing

    while (!minterms.empty())
    {
        vector<Term> newMinterms = combineTerms();
        if (newMinterms.empty())
            break; // stop if no new terms created
        minterms.assign(newMinterms.begin(), newMinterms.end());
    }
}

// get prime implicants
vector<Term> QuineMcTable::getPrimeImplicants() {
    return primeImps;
}

// Get original minterms for use in ImplicantsTable
vector<Term> QuineMcTable::getMinterms() {
    return minterms;
}
