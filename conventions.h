#ifndef CONVENTIONS_H
#define CONVENTIONS_H

#include "general.h"

typedef struct {
  int opcode;
  int funct;
  char instruction_name[4];
  int adress_source[3];
  int adress_destination[3];
} Instruction;


const Instruction table_instruction[] = {
    {0, {}, "mov", {0,1,3}, {1,3}},
    {1, {}, "cmp",{0,1,3}, {0,1,3}},
    {2, 1, "add", {0,1,3}, {1,3}},
    {2, 2, "sub", {0,1,3}, {1,3}},
    {4, {}, "lea", {1}, {1,3}},
    {5, 1, "clr", {}, {1,3}},
    {5, 2, "not", {}, {1,3}},
    {5, 3, "inc", {}, {1,3}},
    {5, 4, "dec", {}, {1,3}},
    {9, 1, "jmp", {}, {1,2}},
    {9, 2, "bne", {}, {1,2}},
    {9, 3, "jsr", {}, {1,2}},
    {12, {}, "red", {}, {1,3}},
    {13, {}, "prn", {}, {0,1,3}},
    {14, {}, "rts", {}, {}},
    {15, {}, "stop", {}, {}}
};

/*This function convert decimal number to binary number and return binary number
  input:
      decimal_number- The number we want to convert in base 2.
      bits_number- number bits of the binary number
    output:
      binary_number- The number after convertion to base 2
*/
char *decimal_to_binary(int decimal_number, int bits_number);

/*This function convert binary number to hexadecimal number and return hexadecimal number as char
  input:
      binary_number- The number we want to convert in base 16, the variable is array lengh 4.
    output:
      hex_number- The number after convertion to base 16, the variable is char type
*/
char convert_binary_to_hex(char *binary_number);

/*This function convert 'word' binary number with 23 bits to hexadecimal number as a string
  input:
      binary_number- The number we want to convert in base 16, the variable is array lengh 24, .
    output:
      hex_number- The number after convertion to base 16, the variable is *char type
*/
char *convert_word_binary_to_hex(char *binary_number);

#endif
