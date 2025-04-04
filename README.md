# Assembler project (C Language)

Created by: Maya Bilic & Noa Mendelovich  
Course: 20465 — Semester 2025A

## Project Overview

This project is an implementation of assembler in C programming language.
It processes '.as' files containing assembly language instructions and translates them into machine code.
The assembler consists from pre-process and two passes and generates the following output files:

* '.am' files - created after the pre-processing stage. This file contains the original .as content with macros expanded.
* '.ob' files - created after the second pass stage. This file contains the machine code instructions in hexdecimal format.
* '.ent' files - created after the second pass stage. Contains all entry labels defined in the source file
* '.ent' files created after the second pass stage. Contains all external labels defined in the source file


## How to run?


Compile the program
```bash
make
```

Run the o files with arguments
```bash
./assembler <filename1> <filename2> ...
```

Clean and reset th program
```bash
make clean
```



