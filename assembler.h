#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LINE_LENGTH 80
#define NUM_INSRUCTION 16

typedef enum { FALSE, TRUE} boolean;
typedef enum {Data, String, Entry, Extern} directive;

typedef struct {
    char *mcro_name;
    char *mcro_lines;
} Mcro;

/*
typedef struct{
    char *part1;
    char *part2;
    char *part3;
    char *part4;
} Split;
*/
typedef struct {
    int opcode;
    int funct;
    char instruction_name[4];
    int adress_source[3];
    int adress_destination[3];
} Instruction;

/*
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
*/

/* This function create full name of the file with extension
    input:
      filename- the name of the file name we want create 
      file_type- the type of the file we want to create its fullname
    output:
      return filename with extension
*/
char *create_fullname_of_file(char *filename, char *file_type);

/* This function check if we can read  from file
    input:
      filename- the name of the file we want to read
      file- the file we try to read, it's a pointer
    output:
      return FALSE if the file is not open for reading else TRUE
*/
boolean file_handling_of_reading(char *filename, FILE **file);

/* This function check if we can write from file
    input:
      filename- the name of the file we want to write
      file- the file we try to write, it's a pointer
    output:
      return FALSE if the file is not open for writing else TRUE
*/
boolean file_handling_of_writing(char *filename, FILE **file);

/* This function aplit line to array of words
    input:
      string_of_line- the line we want to split
    output:
      split_line_words- the array of words after we splitted
*/
char **split_line(char *string_of_line);

/* This function check if the variable is not protected word
    input:
      variable- the variable name we want to check
    output:
      return FALSE if the name is protected name, else TRUE

*/
boolean check_not_protected_word(char *variable_name);

/* This function implement the pre process of the assembler
    input:
      filename- the name of the file we work with
    output:
      if this process going well it will continue to the next pass, else finish to work with this file
*/
int pre_process(char *filename);

/* This function create am file from as file
    input:
      full_filename_as- the name of the file we read from it, source file
      full_filename_am- the name of the file we write to him, destination file
    output:
      if this process going well it will continue to the next pass, else finish to work with this file
*/
void create_am_file(char *input_filename, char *output_filename);

/* This function check if the line of define mcro is correct 
    input:
      array_of_line- the line after we split to array of strings
      count- the number of the words we excpet to be in line
    output:
      return FALSE if the line is not valid and has more then count words number else TRUE
*/
boolean mcro_line_valid(char **array_of_line, int count);

/* This function get the index of the mcro define in line
    input:
      array_of_line- the line after we split to array of strings
      mcro_name- the define of mcro / mcroend
    output:
      return the index of the mcro define in the line
*/
int get_index_of_mcro(char **array_of_line, char *mcro_define);

/* This function check if the line of define mcro is correct 
    input:
      array_of_line- the line after we split to array of strings
      count- the number of the words we excpet to be in line
    output:
      return FALSE if the line is not valid and has more then count words number else TRUE
*/
boolean mcro_line_valid(char **array_of_line, int count);

/* This function check if if the mcro name is valid 
    input:
      mcro_name- the mcro name we want to check
    output:
      return FALSE if the name is not valid for mcro define else TRUE
*/
boolean checking_mcro_name(char *mcro_name);


char *replacing_mcro_name(char *mcro_name);
void Subtracting_spaces(char *string);
void saving_mcro_data(char *mcro_name, char *mcro_lines);

void release_memory();


/*
Split split_line(char *line);
int checking_mcro_name(Split split_copy_line);
void saving_mcro_data(char *mcro_name, char *mcro_lines);
char *replacing_mcro_name(char *mcro_name);
void store_mcros( char *filename);
void create_file_am(char *file_name, char *filename);
void release_memory();
void Subtracting_spaces(char *s);

int checking_register(char *x);
char *decimal_to_binary(int decimal_number, int bits_number);
char convert_binary_to_hex(char *binary_number);
char *convert_word_binary_to_hex(char *binary_number);
*/
