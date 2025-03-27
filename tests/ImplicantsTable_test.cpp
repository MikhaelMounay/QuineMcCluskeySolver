#include <gtest/gtest.h>

#include <vector>

#include "../src/implicants_table/ImplicantsTable.h"

class ImplicantsTableTest : public ::testing::Test {
private:
    Logger* logger = new Logger;
    vector<Term> primeImps = {Term(logger, "00-1", {1, 3}),
                              Term(logger, "001-", {2, 3})};
    vector<Term> minterms = {Term(logger, 1, 4), Term(logger, 2, 4), Term(logger, 3, 4)};
    ImplicantsTable table;

protected:
    Logger* log = logger;

    void SetUp() override {
        table = ImplicantsTable(log, primeImps, minterms, 4);
    }

    string getMinimizedExpression() {
        return table.getMinimizedExpression();
    }

    void createAndSimplifyTable() {
        table.createAndSimplifyTable();
    }

    void eliminateDominatedRows() {
        table.eliminateDominatedRows();
    }

    void eliminateDominatedColumns() {
        table.eliminateDominatedColumns();
    }
};

TEST_F(ImplicantsTableTest, BooleanFunction1) {
    EXPECT_EQ(getMinimizedExpression(), "A'B'D + A'B'C");
}

TEST_F(ImplicantsTableTest, BooleanFunction2) {
    vector<Term> primeImps = {Term(log, "0100", {4}), Term(log, "00-1", {1, 3}),
                              Term(log, "001-", {2, 3})};
    vector<Term> minterms = {Term(log, 1, 4), Term(log, 2, 4), Term(log, 3, 4),
                             Term(log, 4, 4)};
    ImplicantsTable table = ImplicantsTable(log, primeImps, minterms, 4);
    EXPECT_EQ(table.getMinimizedExpression(), "A'BC'D' + A'B'D + A'B'C");
}

TEST_F(ImplicantsTableTest, BooleanFunction3) {
    vector<Term> primeImps = {Term(log, "-0-0", {0, 10, 2, 8}),
                              Term(log, "--10", {10, 14, 2, 6}),
                              Term(log, "1--0", {10, 12, 14, 8}),
                              Term(log, "-1-1", {13, 15, 5, 7}),
                              Term(log, "-11-", {14, 15, 6, 7}),
                              Term(log, "11--", {12, 13, 14, 15})};
    int numVars = 4;
    vector<Term> minterms = {Term(log, 0, numVars), Term(log, 2, numVars),
                             Term(log, 5, numVars), Term(log, 6, numVars),
                             Term(log, 7, numVars), Term(log, 8, numVars),
                             Term(log, 10, numVars), Term(log, 12, numVars),
                             Term(log, 13, numVars), Term(log, 14, numVars),
                             Term(log, 15, numVars)};

    ImplicantsTable table = ImplicantsTable(log, primeImps, minterms, numVars);

    set<string> possibleExpressions = {
        "B'D' + CD' + AD' + BD",
        "B'D' + CD' + AB + BD",
        "B'D' + AD' + BC + BD",
        "B'D' + BC + AB + BD",
    };
    EXPECT_TRUE(possibleExpressions.count(table.getMinimizedExpression()) > 0);
}

// TODO: Unit tests for private functions for intermediate steps
