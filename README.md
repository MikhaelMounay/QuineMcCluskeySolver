# Quine-McCluskey Logic Minimization
CSCE2301 Diginal Design I (Spring 2025) - Project 1
Here's a sample `README.txt` file for your project:

---

# Boolean Function Minimizer

## Overview

This project is a C++ program designed to minimize Boolean functions using the Quine-McCluskey method. The program reads a Boolean function from a text file, processes it to identify prime implicants (PIs) and essential prime implicants (EPIs), and provides the minimized Boolean expression. Additionally, it can generate a Verilog module based on the minimized expression.
## Requirements

- **C++ Compiler**: A C++ compiler is required to build the application.
- **Input File Format**: The input file should have three lines:
    1. The number of variables.
    2. Minterms (indicated by 'm') or maxterms (indicated by 'M'), separated by commas.
    3. Don't-care terms (indicated by 'd'), separated by commas.

## Building the Application

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the source code using a C++ compiler:
   ```bash
    -o QuineMcCluskeySolver main.cpp
   ```
4. Run the application:
   ```bash
   ./QuineMcCluskeySolver
   ```

## Using the Application

1. Prepare an input file named `input.txt` in the same directory as the executable. The file should be formatted as described above.
2. Run the application. It will read from `input.txt` and print the prime implicants, essential prime implicants, minimized Boolean expression, and the Verilog module.

## Example Input File

```plaintext
3
m1,m3,m6,m7
d0,d5
```

This example specifies a Boolean function with 3 variables, minterms 1, 3, 6, and 7, and don't-care terms 0 and 5.

The application will display the following:
- **Prime Implicants**: Binary representation and covered minterms/don't-care terms.
- **Essential Prime Implicants**: Binary representation and covered minterms.
- **Minimized Boolean Expression**: Simplified Boolean expression.
- **Verilog Module**: A basic Verilog module implementing the minimized expression.

**Output**:
```plaintext
Prime Implicants: A'B' , AB , C

Essential Implicants: C , AB

F = AB + C
```
**Verilog**:
```plaintext
`timescale 1ns / 1ps

// Boolean Expression: AB + C

module fn(
	input A, B, C, 
	output X
	);

	wire _1, _2;

	and(_1, A, B);
	and(_2, C, B);

	or(X, _1, _2);

endmodule

```

## Bonus Feature

The application includes a bonus feature to generate a Verilog module based on the minimized Boolean expression.

**Verilog**:
```plaintext
`timescale 1ns / 1ps

// Boolean Expression: AB + C

module fn(
	input A, B, C, 
	output X
	);

	wire _1, _2;

	and(_1, A, B);
	and(_2, C, B);

	or(X, _1, _2);

endmodule

```
