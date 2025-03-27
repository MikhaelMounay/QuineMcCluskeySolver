#include <gtest/gtest.h>

#include "../src/logger/Logger.h"
#include "../src/quine_mc_table/QuineMcTable.h"

class QuineMcTableTest : public ::testing::Test {
private:
    Logger* logger = new Logger;
    vector<Term> minterms = {Term(logger, 0b1010, 4), Term(logger, 0b1000, 4), Term(logger, 0b1100, 4)};
    QuineMcTable QMTable;

protected:
    Logger* log = logger;
    void SetUp() override {
        QMTable = QuineMcTable(log, minterms, 4);
    }

    void sortMintermsByOnes() {
        QMTable.sortMintermsByOnes();
    }

    vector<Term> combineTerms() {
        return QMTable.combineTerms();
    }

    vector<Term> getPrimeImplicants() {
        return QMTable.getPrimeImplicants();
    }
};

TEST_F(QuineMcTableTest, DefaultConstructor) {
    QuineMcTable table;
    EXPECT_EQ(table.getPrimeImplicants().size(), 0);
}

TEST_F(QuineMcTableTest, ConstructorWithMinterms) {
    vector<Term> minterms = {Term(log, 0b0001, 4), Term(log, 0b0011, 4), Term(log, 0b0111, 4)};
    QuineMcTable table(log, minterms, 4);
    EXPECT_EQ(table.getPrimeImplicants().size(), 2);
    // Initial terms are prime implicants
}

// TODO: currently sortMintermsByOnes() and combineTerms() are in-place functions
// TODO: so the minterms vector is being overriden after the constructor call
// TODO: so we can't get intermediate values from these functions for now without making a separate container for each function
// TODO: which is ignored for now for space-wise performance

// TEST_F(QuineMcTableTest, SortMintermsByOnes) {
//     vector<Term> sortedMinterms = sortMintermsByOnes();
//
//     for (int i = 0; i < sortedMinterms.size(); i++) {
//         std::cout << sortedMinterms[i].getBinaryValue() << std::endl;
//     }
//
//     EXPECT_EQ(sortedMinterms[0].getBinaryValue(), "1000"); // Should be first (1 one)
//     EXPECT_EQ(sortedMinterms[1].getBinaryValue(), "1010"); // Second (2 ones)
//     EXPECT_EQ(sortedMinterms[2].getBinaryValue(), "1100"); // Last (2 ones)
// }
//
// TEST_F(QuineMcTableTest, CombineTerms) {
//     vector<Term> combined = combineTerms();
//     EXPECT_EQ(combined.size(), 1);
//     EXPECT_EQ(combined[0].getBinaryValue(), "00-1");
// }

TEST_F(QuineMcTableTest, Solve) {
    vector<Term> minterms = {Term(log, 0b0001, 4), Term(log, 0b0010, 4), Term(log, 0b0011, 4),
                             Term(log, 0b0100, 4)};
    QuineMcTable table(log, minterms, 4);
    vector<Term> primeImplicants = table.getPrimeImplicants();

    EXPECT_EQ(primeImplicants.size(), 3);

    EXPECT_EQ(primeImplicants[0].getBinaryValue(), "0100");
    EXPECT_EQ(primeImplicants[1].getBinaryValue(), "00-1");
    EXPECT_EQ(primeImplicants[2].getBinaryValue(), "001-");
}
