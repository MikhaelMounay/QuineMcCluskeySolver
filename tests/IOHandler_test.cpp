#include <gtest/gtest.h>
#include <fstream>
using namespace std;

#include "../src/logger/Logger.h"
#include "../src/io_handler/IOHandler.h"

// Helper function to create a temporary input file
bool createTempFile(const string& content) {
    string filename = "temp_input.txt";

    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    file << content;

    file.close();
    return true;
}

// Test IOHandler Constructor with file reading
TEST(IOHandlerTest, ConstructorReadsInputFile) {
    Logger log{};
    bool createdSuccessfully = createTempFile("3\nm1,m3,m6,m7\nd0,d5");

    EXPECT_TRUE(createdSuccessfully);

    IOHandler ioHandler(&log, "temp_input.txt");

    EXPECT_EQ(ioHandler.resolveMinimizedExpression(),
              "AB + C");
}

// Test setting input file path
TEST(IOHandlerTest, SetInputFilePath) {
    Logger log{};
    IOHandler ioHandler{};
    ioHandler._setLogger(&log);

    bool createdSuccessfully = createTempFile("3\nm1,m3,m6,m7\nd0,d5");
    EXPECT_TRUE(createdSuccessfully);

    ioHandler.setInputFilePath("temp_input.txt");

    EXPECT_EQ(ioHandler.resolveMinimizedExpression(),
              "AB + C");
}

// Test writing to output files
TEST(IOHandlerTest, WriteToOutputFiles) {
    Logger log{};
    bool createdSuccessfully = createTempFile("3\nm1,m3,m6,m7\nd0,d5");
    EXPECT_TRUE(createdSuccessfully);

    IOHandler ioHandler(&log, "temp_input.txt", "temp_output.txt");
    ioHandler.resolveMinimizedExpression();

    EXPECT_TRUE(ioHandler.writeToOutputFiles());

    ifstream file("temp_output.txt");
    EXPECT_TRUE(file.is_open());

    string content;
    getline(file, content);

    EXPECT_FALSE(content.empty());
    file.close();
}
