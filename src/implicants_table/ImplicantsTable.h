#ifndef IMPLICANTSTABLE_H
#define IMPLICANTSTABLE_H

#include <vector>
using namespace std;

#include "../logger/Logger.h"
#include "../term/Term.h"

class ImplicantsTable {
    friend class ImplicantsTableTest;

private:
    Logger* log;

    vector<Term> primeImps;
    vector<Term> minterms;
    vector<vector<bool>> table;
    int numberOfVariables;

    vector<string> essentialImpsString;

    // Helpers
    void createAndSimplifyTable();
    bool eliminateDominatedRows();
    bool eliminateDominatedColumns();
    void extractEssentialImps();
    vector<vector<Term>> applyPetricksMethod();
    void printTable();

public:
    // Constructors
    ImplicantsTable();
    ImplicantsTable(Logger* Log, vector<Term> PrimeImps, vector<Term> Minterms,
                    int NumberOfVariables);

    // Setters
    void _setLogger(Logger* logger);

    // Helpers
    static string getExpressionFromBinary(const string& binaryValue,
                                          const vector<char>& variables);

    // Methods
    vector<string> getMinimizedExpression();
    vector<string> getEssentialImplicantsString();
};

#endif //IMPLICANTSTABLE_H
