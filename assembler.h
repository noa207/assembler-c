#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void check_file(int argc, char *argv[]);
void read_file_line(char *filename);
void create_file(char *file_name, char *file_type);
void append_line_to_file(char *string, char *full_file_name);
char *decimal_to_binary(int decimal_number, int bits_number);
char convert_binary_to_hex(char *binary_number);
char *convert_word_binary_to_hex(char *binary_number);
