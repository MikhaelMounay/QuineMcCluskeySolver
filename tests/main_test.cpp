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
    for (int i = 0; i < 5; i++) {
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
    Logger log;
    IOHandler ioHandler(&log, testFilepath);
    string result = ioHandler.resolveMinimizedExpression();

    set<string> possibleExpressions = getExpectedResult(testFilepath);
    return (possibleExpressions.count(result) > 0);
}

TEST(MainTest, TestCase01) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test01.txt"));
}

TEST(MainTest, TestCase02) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test02.txt"));
}

TEST(MainTest, TestCase03) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test03.txt"));
}

TEST(MainTest, TestCase04) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test04.txt"));
}

TEST(MainTest, TestCase05) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test05.txt"));
}

TEST(MainTest, TestCase06) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test06.txt"));
}

TEST(MainTest, TestCase07) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test07.txt"));
}

TEST(MainTest, TestCase08) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test08.txt"));
}

TEST(MainTest, TestCase09) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test09.txt"));
}

TEST(MainTest, TestCase10) {
    EXPECT_TRUE(runTestCase("../../tests/test_cases/test10.txt"));
}
