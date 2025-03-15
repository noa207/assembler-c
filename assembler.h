#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

enum { FALSE =0,TRUE =1} Boolean;
typedef enum {Data, String, Entry, Extern} directive;

typedef struct {
    char *mcro_name;
    char *mcro_lines;
} Mcro;

typedef struct{
    char *part1;
    char *part2;
    char *part3;
    char *part4;
} Split;

typedef struct {
    int opcode;
    int funct;
    char instruction_name[4];
    int adress_source[3];
    int adress_destination[3];
} Instruction;



typedef enum { FALSE, TRUE} boolean;

void check_file(int argc, char *argv[]);
void read_file_line(char *filename);
void create_file(char *file_name, char *file_type);
void append_line_to_file(char *string, char *full_file_name);

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

