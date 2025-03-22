//
// Created by salma waleed on 20/03/2025.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

// Function to convert decimal to binary string
string decToBin(int num, int bits) {
    bitset<32> b(num);
    string bin = b.to_string();
    return bin.substr(bin.size() - bits);
}

// Structure to represent a prime implicant
struct PrimeImplicant {
    string binary;
    vector<int> minterms;
    vector<int> dontCares;
};

// Function to generate prime implicants
vector<PrimeImplicant> generatePrimeImplicants(int numVars, vector<int> minterms, vector<int> dontCares) {
    vector<PrimeImplicant> primeImplicants;
    // Simplified logic to generate prime implicants
    for (int minterm : minterms) {
        PrimeImplicant pi;
        pi.binary = decToBin(minterm, numVars);
        pi.minterms.push_back(minterm);
        primeImplicants.push_back(pi);
    }
    for (int dontCare : dontCares) {
        // Add logic to handle don't-care terms
    }
    return primeImplicants;
}

// Function to find essential prime implicants
vector<PrimeImplicant> findEssentialPrimeImplicants(vector<PrimeImplicant> primeImplicants, vector<int> minterms) {
    vector<PrimeImplicant> essentialPIs;
    // Simplified logic to find essential prime implicants
    for (PrimeImplicant pi : primeImplicants) {
        bool isEssential = false;
        for (int minterm : pi.minterms) {
            bool covered = false;
            for (PrimeImplicant otherPi : primeImplicants) {
                if (otherPi.minterms.size() > 1 && find(otherPi.minterms.begin(), otherPi.minterms.end(), minterm) != otherPi.minterms.end()) {
                    covered = true;
                    break;
                }
            }
            if (!covered) {
                isEssential = true;
                break;
            }
        }
        if (isEssential) {
            essentialPIs.push_back(pi);
        }
    }
    return essentialPIs;
}

// Function to solve the PI table and minimize the Boolean expression
string minimizeBooleanExpression(vector<PrimeImplicant> primeImplicants, vector<int> minterms) {
    string minimizedExpression = "";
    // Simplified logic to minimize the Boolean expression
    for (PrimeImplicant pi : primeImplicants) {
        if (pi.minterms.size() == 1) {
            minimizedExpression += decToBin(pi.minterms[0], pi.binary.size()) + " + ";
        }
    }
    return minimizedExpression.substr(0, minimizedExpression.size() - 3); // Remove trailing " + "
}

// Function to generate Verilog module (bonus)
string generateVerilogModule(string minimizedExpression) {
    string verilogModule = "module func(\n";
    // Add input variables
    verilogModule += "    input [2:0] in,\n";
    verilogModule += "    output out\n";
    verilogModule += ");\n";
    verilogModule += "assign out = " + minimizedExpression + ";\n";
    verilogModule += "endmodule";
    return verilogModule;
}

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    int numVars;
    string line;
    getline(inputFile, line);
    numVars = stoi(line);

    vector<int> minterms;
    getline(inputFile, line);
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',')) {
        if (token[0] == 'm') {
            minterms.push_back(stoi(token.substr(1)));
        }
    }

    vector<int> dontCares;
    getline(inputFile, line);
    ss.clear();
    ss.str(line);
    while (getline(ss, token, ',')) {
        if (token[0] == 'd') {
            dontCares.push_back(stoi(token.substr(1)));
        }
    }

    inputFile.close();

    // Generate and print prime implicants
    vector<PrimeImplicant> primeImplicants = generatePrimeImplicants(numVars, minterms, dontCares);
    cout << "Prime Implicants:" << endl;
    for (PrimeImplicant pi : primeImplicants) {
        cout << "Binary: " << pi.binary << ", Minterms: ";
        for (int minterm : pi.minterms) {
            cout << minterm << " ";
        }
        cout << endl;
    }

    // Find and print essential prime implicants
    vector<PrimeImplicant> essentialPIs = findEssentialPrimeImplicants(primeImplicants, minterms);
    cout << "\nEssential Prime Implicants:" << endl;
    for (PrimeImplicant pi : essentialPIs) {
        cout << "Binary: " << pi.binary << ", Minterms: ";
        for (int minterm : pi.minterms) {
            cout << minterm << " ";
        }
        cout << endl;
    }

    // Solve PI table and print minimized Boolean expression
    string minimizedExpression = minimizeBooleanExpression(primeImplicants, minterms);
    cout << "\nMinimized Boolean Expression: " << minimizedExpression << endl;

    // Generate Verilog module (bonus)
    string verilogModule = generateVerilogModule(minimizedExpression);
    cout << "\nVerilog Module:\n" << verilogModule << endl;

    return 0;
}
