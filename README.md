# Assembler project (C Language)

Created by: Maya Bilic & Noa Mendelovich  
Course: 20465 — Semester 2025A

## Project Overview

This project is an implementation of assembler language in C programming language.
It executes '.as' files whoch contain assembly language instructions and translates them into machine code language
In each pass the program create the next files:
* '.am' files are created after the pre-process, when we interpret macros- contain as. file's content after interpretation
* '.ob' files created after the second pass when we translate the statements and save them as hexdecimal numbers
* '.ent' files created after the second pass, contains entry labels
* '.ent' files created after the second pass, contains external labels


## How to run?


// Compile the program
```bash
make
```

//Run the o files with arguments
```bash
./assembler <filename1> <filename2> ...
```

//Clean and reset th program
```bash
make clean
```



