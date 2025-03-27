#include <gtest/gtest.h>
#include "../src/term/Term.h"

TEST(TermTest, DefaultConstructor) {
    Term term;
    EXPECT_EQ(term.getBinaryValue(), "");
    EXPECT_FALSE(term.isCombined());
}

TEST(TermTest, DecimalConstructor) {
    Term term(new Logger, 5, 4);
    EXPECT_EQ(term.getBinaryValue(), "0101");
    EXPECT_FALSE(term.isCombined());
}

TEST(TermTest, BinaryConstructor) {
    std::set<int> covered = {1, 5};
    Term term(new Logger, "-101", covered);
    EXPECT_EQ(term.getBinaryValue(), "-101");
    EXPECT_FALSE(term.isCombined());
}

TEST(TermTest, CanCombine) {
    Term term1(new Logger, 5, 4);  // "0101"
    Term term2(new Logger, 7, 4);  // "0111"
    EXPECT_TRUE(term1.canCombineWith(term2));
}

TEST(TermTest, CannotCombine) {
    Term term1(new Logger, 5, 4);  // "0101"
    Term term2(new Logger, 3, 4);  // "0011"
    EXPECT_FALSE(term1.canCombineWith(term2));
}

TEST(TermTest, CombineWith) {
    Term term1(new Logger, 5, 4);  // "0101"
    Term term2(new Logger, 7, 4);  // "0111"
    Term combined = term1.combineWith(&term2);
    EXPECT_EQ(combined.getBinaryValue(), "01-1");
    EXPECT_TRUE(combined.canCombineWith(term1));
    EXPECT_TRUE(combined.canCombineWith(term2));

    EXPECT_TRUE(term1.isCombined());
    EXPECT_TRUE(term2.isCombined());
    EXPECT_FALSE(combined.isCombined());
}

TEST(TermTest, SetCombinedFlag) {
    Term term(new Logger, 5, 4);
    EXPECT_FALSE(term.isCombined());
    term.setCombined(true);
    EXPECT_TRUE(term.isCombined());
}
