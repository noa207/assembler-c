#ifndef GENERAL_H
#define GENERAL_H

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LINE_LENGTH 80
#define NUM_PROTECTED_WORDS 26

typedef enum { FALSE, TRUE} boolean;

/* This function aplit line to array of words
    input:
      string_of_line- the line we want to split
    output:
      split_line_words- the array of words after we splitted
*/
char **split_line(char *string_of_line);

/*

*/
/*void split_line_memory_release(char **split_line_words);*/

/* This function check if the variable is not protected word
    input:
      variable- the variable name we want to check
    output:
      return FALSE if the name is protected name, else TRUE

*/
boolean check_not_protected_word(char *variable_name);

/*This function cleans up spaces from the beginning of a word
    input:
       token - the token we want to clean from spaces
*/
void Subtracting_spaces(char *string);


#endif
