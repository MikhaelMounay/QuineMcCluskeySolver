#include "ImplicantsTable.h"

#include <algorithm>
#include <unordered_map>
#include <iostream>
using namespace std;

// Constructors
ImplicantsTable::ImplicantsTable() {
    log = new Logger();

    primeImps = {};
    minterms = {};
    numberOfVariables = 0;
    table = {};
}

ImplicantsTable::ImplicantsTable(Logger* Log, vector<Term> PrimeImps,
                                 vector<Term> Minterms, int NumberOfVariables) {
    log = Log;

    primeImps = move(PrimeImps);
    minterms = move(Minterms);
    numberOfVariables = NumberOfVariables;

    createAndSimplifyTable();
}

// Helpers
void ImplicantsTable::createAndSimplifyTable() {
    int numMinterms = minterms.size();
    int numImplicants = primeImps.size();

    // Initialize chart with false
    table.resize(numImplicants, vector<bool>(numMinterms, false));

    // Fill the chart: If the implicant covers the minterm, set chart[i][j] = true
    for (int i = 0; i < numImplicants; i++) {
        for (int j = 0; j < numMinterms; j++) {
            if (primeImps[i].covers(minterms[j])) {
                table[i][j] = true;
            }
        }
    }

    *log << "[ImplicantsTable] Prime Implicants Chart: " << endl;
    printTable();

    // Note: in order to print all possible minimized expressions of a function
    // eliminateDominatedRows() won't eliminate equal rows
    // and equal rows are left to applyPetricksMethod to get all possible combinations
    bool repeatFlag = false;
    do {
        repeatFlag = eliminateDominatedRows();
        *log <<
            "[ImplicantsTable] Prime Implicants Chart after dominated rows elimination: "
            << endl;
        printTable();
        if (!repeatFlag) {
            repeatFlag = eliminateDominatedColumns();
        } else {
            eliminateDominatedColumns();
        }
        *log <<
            "[ImplicantsTable] Prime Implicants Chart after dominated columns elimination: "
            << endl;
        printTable();
    } while (repeatFlag);

    extractEssentialImps();
}

bool ImplicantsTable::eliminateDominatedRows() {
    int numRows = table.size();
    int numCols = table[0].size();

    vector<bool> dominated(numRows, false);

    // Compare each row with every other row to find dominated rows
    for (int i = 0; i < numRows; i++) {
        if (dominated[i]) {
            continue;
        }

        for (int j = 0; j < numRows; j++) {
            if (i == j || dominated[j]) {
                continue;
            }

            // Check if rows i and j are equal
            bool equalRows = true;
            for (int k = 0; k < numCols; k++) {
                if (table[i][k] != table[j][k]) {
                    equalRows = false;
                    break;
                }
            }

            if (equalRows) {
                break;
            }

            // If row i dominates row j (covers the same or more minterms)
            bool isDominated = true;
            for (int k = 0; k < numCols; k++) {
                if (table[i][k] < table[j][k]) {
                    isDominated = false;
                    break;
                }
            }

            if (isDominated) {
                dominated[j] = true; // Mark row j as dominated
            }
        }
    }

    // Remove dominated rows from the chart
    *log << "[ImplicantsTable] Dominated Rows: ";
    for (int i = numRows - 1; i >= 0; i--) {
        if (dominated[i]) {
            *log << i << " ";
            table.erase(table.begin() + i);
            primeImps.erase(primeImps.begin() + i);
        }
    }
    *log << endl;

    return (numRows != table.size());
}

bool ImplicantsTable::eliminateDominatedColumns() {
    int numRows = table.size();
    int numCols = table[0].size();

    vector<bool> dominated(numCols, false);

    // Compare each column with every other column to find dominated columns
    for (int j = 0; j < numCols; j++) {
        if (dominated[j]) {
            continue;
        }

        for (int k = 0; k < numCols; k++) {
            if (j == k || dominated[k]) {
                continue;
            }

            // If column j dominates column k (is covered by more or equal implicants)
            bool isDominated = true;
            for (int i = 0; i < numRows; i++) {
                if (table[i][j] < table[i][k]) {
                    isDominated = false;
                    break;
                }
            }

            if (isDominated) {
                dominated[j] = true; // Mark column k as dominated
            }
        }
    }

    // Remove dominated columns from the chart
    *log << "[ImplicantsTable] Dominated Columns: ";
    for (int j = numCols - 1; j >= 0; j--) {
        if (dominated[j]) {
            *log << j << " ";
            for (int i = 0; i < numRows; i++) {
                table[i].erase(table[i].begin() + j);
            }
            minterms.erase(minterms.begin() + j);
        }
    }
    *log << endl;

    return (numCols != table[0].size());
}

void ImplicantsTable::extractEssentialImps() {
    vector<char> variables(numberOfVariables);
    for (int i = 0; i < numberOfVariables; i++) {
        variables[i] = static_cast<char>(65 + i);
    }

    *log << "[ImplicantsTable] Essential Implicants: ";
    unordered_map<string, int> uniqueRows;
    for (int i = 0; i < primeImps.size(); i++) {
        string row;
        for (int j = 0; j < table[i].size(); j++) {
            row += to_string(table[i][j]);
        }

        if (uniqueRows.contains(row)) {
            uniqueRows.erase(row);
        } else {
            uniqueRows[row] = i;
        }
    }

    for (auto it = uniqueRows.begin(); it != uniqueRows.end(); it++) {
        string s = getExpressionFromBinary(
            primeImps[it->second].getBinaryValue(),
            variables);
        essentialImpsString.push_back(s);
        *log << s;

        if (next(it) != uniqueRows.end()) {
            *log << " , ";
        }
    }
    *log << endl << endl;
}

// TODO: needs a bit of tweaking
vector<vector<Term>> ImplicantsTable::applyPetricksMethod() {
    int numRows = table.size();
    int numCols = table[0].size();
    vector<vector<int>> terms(numCols);

    // Constructing Boolean expression as a sum of products
    for (int j = 0; j < numCols; j++) {
        for (int i = 0; i < numRows; i++) {
            if (table[i][j]) {
                terms[j].push_back(i);
            }
        }

        *log << "[PetricksMethod] Term " << j << ": ";
        for (int k = 0; k < terms[j].size(); k++) {
            *log << terms[j][k] << " ";
        }
        *log << endl << endl;
    }

    // Generating all possible product terms
    vector<set<int>> products = {{terms[0].begin(), terms[0].end()}};
    for (int i = 1; i < numCols; i++) {
        vector<set<int>> newProducts;

        for (int j = 0; j < products.size(); j++) {
            for (int k = 0; k < terms[i].size(); k++) {
                set<int> newProd = products[j];

                newProd.insert(terms[i][k]);
                newProducts.push_back(newProd);
            }
        }

        // Remove duplicates within newProducts
        // Not actually need; just for debugging purposes
        // Could be removed to enhance performance
        set<set<int>> uniqueProducts(newProducts.begin(), newProducts.end());
        products.assign(uniqueProducts.begin(), uniqueProducts.end());
        // products = move(newProducts);

        *log << "[PetricksMethod] Products after step " << i << ": ";
        for (int k = 0; k < products.size(); k++) {
            *log << "{ ";
            for (auto it = products[k].begin(); it != products[k].end(); it++) {
                *log << *it << " ";
            }
            *log << "} ";
        }
        *log << endl << endl;
    }

    // Finding the minimal product terms
    int minSize = INT_MAX;
    vector<set<int>> minimalProducts;

    for (int i = 0; i < products.size(); i++) {
        if (products[i].size() < minSize) {
            minSize = products[i].size();
            minimalProducts.clear();
            minimalProducts.push_back(products[i]);
        } else if (products[i].size() == minSize) {
            minimalProducts.push_back(products[i]);
        }
    }

    // Could return a possible answer or all of them if needed
    vector<vector<Term>> essentialImplicants(minimalProducts.size());
    for (int i = 0; i < minimalProducts.size(); i++) {
        for (auto it = minimalProducts[i].begin();
             it != minimalProducts[i].end(); it++) {
            essentialImplicants[i].push_back(primeImps[*it]);

            *log << *it << " ";
        }
        *log << endl;
    }
    *log << endl;

    return essentialImplicants;
}

string ImplicantsTable::getExpressionFromBinary(const string& binaryValue,
                                                const vector<char>& variables) {
    stringstream expression;
    for (int i = 0; i < binaryValue.size(); i++) {
        if (binaryValue[i] == '1') {
            expression << variables[i];
        } else if (binaryValue[i] == '0') {
            expression << variables[i] << "'";
        }
    }
    return expression.str();
}

void ImplicantsTable::printTable() {
    for (int i = 0; i < table.size(); i++) {
        if (i == 0) {
            for (int j = 0; j < numberOfVariables * 1.5; j++) {
                *log << " ";
            }
            for (int j = 0; j < minterms.size(); j++) {
                *log << minterms[j].getDecimalValue() << " ";
            }
            *log << endl;
        }

        *log << primeImps[i].getBinaryValue() << " | ";

        for (int j = 0; j < table[i].size(); j++) {
            *log << table[i][j] << " ";
        }
        *log << endl;
    }
    *log << endl;
}

// Setters
void ImplicantsTable::_setLogger(Logger* logger) {
    log = logger;
}

// Methods
vector<string> ImplicantsTable::getMinimizedExpression() {
    vector<string> possibleMinimizedExpressions;

    vector<char> variables(numberOfVariables);
    for (int i = 0; i < numberOfVariables; i++) {
        variables[i] = static_cast<char>(65 + i);
    }

    vector<vector<Term>> impsCombinations = applyPetricksMethod();

    for (int i = 0; i < impsCombinations.size(); i++) {
        vector<string> expressionTerms;

        for (int j = 0; j < impsCombinations[i].size(); j++) {
            string binaryValue = impsCombinations[i][j].getBinaryValue();
            string expressionTerm = getExpressionFromBinary(
                binaryValue, variables);

            if (expressionTerm.empty()) {
                *log << "[ImplicantsTable] Minimized Expression: " << 1 << endl;
                return {"1"};
            }

            expressionTerms.push_back(expressionTerm);
        }

        string minimizedExpression = expressionTerms[0];
        for (int k = 1; k < expressionTerms.size(); k++) {
            minimizedExpression += " + " + expressionTerms[k];
        }
        possibleMinimizedExpressions.push_back(minimizedExpression);

        *log << "[ImplicantsTable] Minimized Expression: " <<
            minimizedExpression << endl;
    }
    *log << endl;

    return possibleMinimizedExpressions;
}

vector<string> ImplicantsTable::getEssentialImplicantsString() {
    return essentialImpsString;
}
