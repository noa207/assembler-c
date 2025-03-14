#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

enum { FALSE =0,TRUE =1} Boolean;

typedef struct {
    char *mcro_name;
    char *mcro_lines;
} mcro;

typedef struct{
    char *part1;
    char *part2;
    char *part3;
    char *part4;
} split;

typedef struct {
    int opcode;
    int funct;
    char instruction_name[4];
    int adress_source[3];
    int adress_destination[3];
} instruction;
/*extern instruction table_instruction[];*/


void check_file(int argc, char *argv[]);
void read_file_line(char *filename);
void create_file(char *file_name, char *file_type);
void append_line_to_file(char *string, char *full_file_name);
split split_line(char *line);
int checking_mcro_name(split split_copy_line);
void saving_mcro_data(char *mcro_name, char *mcro_lines);
char *replacing_mcro_name(char *mcro_name);
void store_mcros( char *filename);
void create_file_am(char *file_name, char *filename);
void release_memory();