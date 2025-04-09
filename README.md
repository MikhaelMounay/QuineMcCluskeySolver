# Quine-McCluskey Solver (Logic Functions Minimization)
CSCE2301 Diginal Design I (Spring 2025) - Project 1

## Overview

This project is a C++ console app designed to minimize Boolean functions using the Quine-McCluskey method.

The program reads a Boolean function from a text file, processes it to identify prime implicants (PIs) and essential prime implicants (EPIs), and provides the minimized Boolean expression. Additionally, it can generate a Verilog module based on the minimized expression.

## Usage

The app can be used from console as follows:

`./QuineMcCluskeySolver-vx.x-arch-os [-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>`

*You can easily download and use the prebuilt binaries from the repos the **GitHub Releases** page.*

### CLI Switches/Flags

- `<input_file>`: filename with the input written in the specified format below
- `-v` (optional): verbose output
- `-d <dump_log_file>` (optional): filename to dump the log to (including solving steps and the final output)
- `-o <output_file>` (optional): filename to save the output to
- `--verilog <verilog_file>` (optional): filename to save the Verilog Module to


### Input File Format
The input file should have three lines:
1. The number of variables.
2. Minterms (indicated by 'm') or maxterms (indicated by 'M'), separated by commas.
3. Don't-care terms (indicated by 'd'), separated by commas.


### Example

#### Input File
```plaintext
3
m1,m3,m6,m7
d0,d5
```

#### Output
```plaintext
Prime Implicants:
[01] A'B'        covers: 0 | 1
[02] AB  covers: 6 | 7
[03] C   covers: 1 | 3 | 5 | 7

Essential Implicants:
[01] C   covers: 1 | 3 | 5 | 7
[02] AB  covers: 6 | 7

Possible Minimizations:
[01] F = AB + C
```

#### Verilog Output (with the `--verilog` flag)
```verilog
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

## Limitations
- Although the program can theoretically process up to 20-variable functions, due to some memory limits, the program might crash if the number of minterms provided is too large, or the number of maxterms provided is too small.

---

# For Developers
## Building from Source

1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the source code using a C++ compiler (the project is `CMake`-dependent; `GCC` was used during developed period):

    ```bash
    cmake.exe --build cmake-build-profile_name --target QuineMcCluskeySolver
    ```

    *Notice that you have to have CMake and a C++ compiler installed on your computer beforehand!*

    For release builds, [Zig](https://ziglang.org/) is used for more optimized and cross-compiled binaries (the `build.zig` file is already prepared in the repo)
        
    ```bash
    zig build --release
    ```    

    *Notice that you have to have the Zig compiler installed on your computer beforehand!*


4. Run the application:
   ```bash
   ./QuineMcCluskeySolver [-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>
   ```

---

## Contributors

- [Mikhael Khalil](https://github.com/MikhaelMounay)
- [Marina Nazeh](https://github.com/MarinaNazeh)
- [Salma ElMarakby](https://github.com/salmawaleed055)
