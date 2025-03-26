#ifndef QUINEMCTABLE_H
#define QUINEMCTABLE_H

#include <vector>
using namespace std;

#include "../logger/Logger.h"
#include "../term/Term.h"

class QuineMcTable {
    friend class QuineMcTableTest;

private:
    Logger* log;

    int numberOfVariables;
    vector<Term> minterms;
    vector<Term> _minterms;
    vector<Term> primeImps;
    vector<vector<string>> table;

    // Helpers
    void createTable();
    void solve();
    void sortMintermsByOnes();
    static bool compareTerms(Term& a, Term& b);
    vector<Term> combineTerms();

    // Utils
    void _logData();

public:
    // Constructors
    QuineMcTable();
    QuineMcTable(vector<Term> Minterms, int NumberOfVariables);

    // Setters
    void _setLogger(Logger* logger);

    // Methods
    vector<Term> getPrimeImplicants();
};

#endif //QUINEMCTABLE_H
