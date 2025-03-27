#include <gtest/gtest.h>
#include <fstream>
using namespace std;

#include "../src/io_handler/IOHandler.h"

// Helper function to get the expected output from the test case files
set<string> getExpectedResult(const string& testFilepath) {
    ifstream testFile(testFilepath);
    if (!testFile.is_open()) {
        cerr << "Error opening test file " << testFilepath << endl;
        exit(1);
    }

    string line;
    for (int i = 0; i < 4; i++) {
        getline(testFile, line);
    }

    stringstream possibleExpressionsLine(line);
    set<string> possibleExpressions;

    string possibleExpression;
    while (getline(possibleExpressionsLine, possibleExpression, ',')) {
        possibleExpressions.insert(possibleExpression);
    }

    testFile.close();

    return possibleExpressions;
}

// Helper function to run test cases
bool runTestCase(const string& testFilepath) {
    Logger log{&cout};
    IOHandler ioHandler(&log, testFilepath);
    string result = ioHandler.resolveMinimizedExpression();

    set<string> possibleExpressions = getExpectedResult(testFilepath);
    return (possibleExpressions.count(result) > 0);
}

TEST(MainTest, TestCase01) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_01.txt"));
}

TEST(MainTest, TestCase02) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_02.txt"));
}

TEST(MainTest, TestCase03) {
    EXPECT_EXIT(runTestCase("../../tests/test_cases/test_03.txt"), ::testing::ExitedWithCode(1), "Error: please provide a valid input for minterms");
}

TEST(MainTest, TestCase04) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_04.txt"));
}

TEST(MainTest, TestCase05) {
    EXPECT_EXIT(runTestCase("../../tests/test_cases/test_05.txt"), ::testing::ExitedWithCode(1), "minterms and don't cares shouldn't overlap");
}

// TEST(MainTest, TestCase06) {
//     EXPECT_TRUE(runTestCase("../../tests/test_cases/test_06.txt"));
// }

TEST(MainTest, TestCase07) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_07.txt"));
}

TEST(MainTest, TestCase08) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_08.txt"));
}

TEST(MainTest, TestCase09) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_09.txt"));
}

TEST(MainTest, TestCase10) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test_10.txt"));
}
