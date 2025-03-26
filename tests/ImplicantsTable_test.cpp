#include <gtest/gtest.h>

#include <vector>

#include "../src/implicants_table/ImplicantsTable.h"

class ImplicantsTableTest : public ::testing::Test {
private:
    vector<Term> primeImps = {Term("00-1", {1, 3}), Term("001-", {2, 3})};
    vector<Term> minterms = {Term(1, 4), Term(2, 4), Term(3, 4)};
    ImplicantsTable table;

protected:
    void SetUp() override {
        table = ImplicantsTable(primeImps, minterms, 4);
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
    vector<Term> primeImps = {Term("0100", {4}), Term("00-1", {1, 3}),
                              Term("001-", {2, 3})};
    vector<Term> minterms = {Term(1, 4), Term(2, 4), Term(3, 4), Term(4, 4)};
    ImplicantsTable table = ImplicantsTable(primeImps, minterms, 4);
    EXPECT_EQ(table.getMinimizedExpression(), "A'BC'D' + A'B'D + A'B'C");
}

TEST_F(ImplicantsTableTest, BooleanFunction3) {
    vector<Term> primeImps = {Term("-0-0", {0, 10, 2, 8}),
                              Term("--10", {10, 14, 2, 6}),
                              Term("1--0", {10, 12, 14, 8}),
                              Term("-1-1", {13, 15, 5, 7}),
                              Term("-11-", {14, 15, 6, 7}),
                              Term("11--", {12, 13, 14, 15})};
    int numVars = 4;
    vector<Term> minterms = {Term(0, numVars), Term(2, numVars),
                             Term(5, numVars), Term(6, numVars),
                             Term(7, numVars), Term(8, numVars),
                             Term(10, numVars), Term(12, numVars),
                             Term(13, numVars), Term(14, numVars),
                             Term(15, numVars)};
    ImplicantsTable table = ImplicantsTable(primeImps, minterms, numVars);

    set<string> possibleExpressions = {
        "B'D' + BD + CD' + AD'",
        "B'D' + BD + CD' + AB",
        "B'D' + BD + AD' + BC",
        "B'D' + BD + BC + AB",
    };
    EXPECT_TRUE(possibleExpressions.count(table.getMinimizedExpression()) > 0);
}

// TODO: Unit tests for private functions for intermediate steps
