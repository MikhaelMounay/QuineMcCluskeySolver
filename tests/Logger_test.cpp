#include <gtest/gtest.h>
#include "../src/logger/Logger.h"

using namespace std;

TEST(LoggerTest, DefaultConstructor) {
    Logger log;
    log << "This should be logged only to the static ostringstream.";
    EXPECT_EQ(log.get_ostream()->tellp(), std::streampos(string("This should be logged only to the static ostringstream.").length()));
}

TEST(LoggerTest, ConstructorWithStream) {
    ostringstream oss;
    Logger log(&oss);
    log << "Hello, Logger!";
    EXPECT_EQ(oss.str(), "Hello, Logger!");
}

TEST(LoggerTest, LoggingMultipleValues) {
    ostringstream oss;
    Logger log(&oss);
    log << "Value: " << 42 << ", Pi: " << 3.14;
    EXPECT_EQ(oss.str(), "Value: 42, Pi: 3.14");
}

TEST(LoggerTest, LoggingWithManipulators) {
    ostringstream oss;
    Logger log(&oss);
    log << "First Line" << endl << "Second Line";
    EXPECT_EQ(oss.str(), "First Line\nSecond Line");
}
