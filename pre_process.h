#ifndef PRE_PROCESS_H
#define PRE_PROCESS_H

#include "general.h"
#include "files.h"


typedef struct Mcro {
    char *mcro_name;
    char *mcro_lines;
} Mcro;

/* a pointer to the mcros array */
typedef struct MacrosArray {
  Mcro* mcros;
  int number_of_mcros;
} MacrosArray;

/* This function implement the pre process of the assembler
    input:
      filename- the name of the file we work with
    output:
      if this process going well it will continue to the next pass, else finish to work with this file
*/
int pre_process(char *filename);

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
int mcro_get_index(char **array_of_line, char *mcro_define);

/* This function check if the mcro name is valid
    input:
      mcro_name- the mcro name we want to check
    output:
      return FALSE if the name is not valid for mcro define else TRUE
*/
boolean mcro_name_checking(char *mcro_name, int line_counter);

/*This function check if the token in the line is a mcro name
    input:
       mcro_name- the token we want to check
    output:
       return the mcro content
*/
char *mcro_insert_data(char *mcro_name);

/*This function store mcro name and mcro content
    input:
       mcro_name- the name of the mcro
       mcro_lines -  the mcro content
*/
void mcro_data_saving(char *mcro_name, char *mcro_lines, int line_counter);

/* This function going through the array release the memory
   input:
     pointer to the beginning of the array
 */

/*void mcro_memory_release();*/

/* This function going through the array and checks whether the string is equal to one of the existing macro names
   input:
     string - The string we want to compare to the mcro names
   output:
      the function returns false if the string is equal to one of the macro names, otherwise true
*/
boolean mcro_array_scan_result( char *string, int line_counter);

/* This function frees the memory allocated of mcro array */
void mcro_memory_release(void);

#endif
