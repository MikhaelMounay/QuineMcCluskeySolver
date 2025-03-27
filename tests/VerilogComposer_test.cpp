#include <gtest/gtest.h>

#include <fstream>

#include "../src/verilog_composer/VerilogComposer.h"

TEST(VerilogComposerTest, DefaultConstructor) {
    VerilogComposer verilogComposer;
    EXPECT_EQ(verilogComposer.getVerilogCode(), "");

    // EXPECT_FALSE(
    //     verilogComposer.saveToFile(
    //         "VerilogComposerTest_DefaultConstructor_test_verilog_module.v")); // (deprecated; responsibility handed to IOHandler)
}

TEST(VerilogComposerTest, ConstructorWithExpression) {
    Logger log;

    VerilogComposer verilogComposer(&log, "AB + C'D");
    EXPECT_EQ(verilogComposer.getVerilogCode(),
              "`timescale 1ns / 1ps\n\n// Boolean Expression: AB + C'D\n\nmodule fn(\n\tinput A, B, C, D, \n\toutput X\n\t);\n\n\twire _1, _2;\n\n\tand(_1, A, B);\n\tand(_2, ~C, D);\n\n\tor(X, _1, _2);\n\nendmodule\n");

}

// Test Save To File (deprecated; responsibility handed to IOHandler)
// TEST(VerilogComposerTest, SaveToFile) {
//     VerilogComposer verilogComposer(new Logger, "AB + C'D");
//     EXPECT_TRUE(verilogComposer.saveToFile("VerilogComposerTest_SaveToFile_test_verilog_module.v"));
//     EXPECT_FALSE(verilogComposer.saveToFile(""));
//
//     ifstream file("VerilogComposerTest_SaveToFile_test_verilog_module.v");
//     string verilogCode;
//     if (file.is_open()) {
//         stringstream fileContent;
//         fileContent << file.rdbuf();
//         verilogCode = fileContent.str();
//         file.close();
//     }
//     EXPECT_EQ(verilogComposer.getVerilogCode(), verilogCode);
// }
