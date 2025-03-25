#ifndef IMPLICANTSTABLE_H
#define IMPLICANTSTABLE_H

#include <vector>
using namespace std;

#include "../logger/Logger.h"
#include "../term/Term.h"

class ImplicantsTable {
private:
    Logger* log;

    vector<Term> primeImps;
    vector<Term> minterms;
    vector<vector<bool>> table;

    // Helpers
    void createAndSimplifyTable();
    void eliminateDominatedRows();
    void eliminateDominatedColumns();

public:
    // Constructors
    ImplicantsTable();
    ImplicantsTable(vector<Term> PrimeImps, vector<Term> Minterms);

    // Setters
    void _setLogger(Logger* logger);

    // Methods
    string getMinimizedExpression();
};

#endif //IMPLICANTSTABLE_H
