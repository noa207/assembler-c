//
// Created by Maya Bilic on 13/03/2025.
//
#include "assembler.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_LINE_LENGTH 80
#define NUM_INSRUCTION 16

Mcro *mcros = NULL;
int number_of_mcros = 0;

Instruction table_instruction[] = {
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

/* Storing the name and content of the macros in the dynamic array */
void saving_mcro_data(char *mcro_name, char *mcro_lines) {
    Mcro *new_mcros = realloc(mcros,(number_of_mcros + 1) * sizeof(Mcro));
    if (new_mcros == NULL) {
        fprintf(stderr,"MEMORY ERROR: allocation failed");
        exit(EXIT_FAILURE);
    }
    mcros = new_mcros;

    /* Allocating memory for the macro name and store */
    mcros[number_of_mcros].mcro_name = malloc(strlen(mcro_name) + 1);
    if (mcros[number_of_mcros].mcro_name == NULL) {
        fprintf(stderr,"MEMORY ERROR: allocation failed - mcro name");
        exit(EXIT_FAILURE);
    }
    strcpy(mcros[number_of_mcros].mcro_name, mcro_name);

    /* Allocating memory for the macro content and store */
    mcros[number_of_mcros].mcro_lines = malloc(strlen(mcro_lines) + 1);
    if (mcros[number_of_mcros].mcro_lines == NULL) {
        fprintf(stderr,"MEMORY ERROR: allocation failed - mcro lines");
        exit(EXIT_FAILURE);
    }
    strcpy(mcros[number_of_mcros].mcro_lines, mcro_lines);
    //printf("%s%s", mcro_name   , mcro_lines);
    number_of_mcros++;
}


/* The function receives a pointer to a name and checks whether the name is in the macro array, if so, replaces the line with the macro value. ֿֿ*/
char *replacing_mcro_name(char *mcro_name) {
    int i;
    for (i = 0; i<number_of_mcros ; i++) {
         if (strcmp(mcros[i].mcro_name, mcro_name) == 0) {
             return mcros[i].mcro_lines;
         }
         //printf("%s%s", mcros[i].mcro_name, mcros[i].mcro_lines);
    }
    return NULL;
}

/* The function traverses the file line by line and stores the macros. */
void store_mcros( char *filename){
    char line[MAX_LINE_LENGTH];
    char mcro_names[MAX_LINE_LENGTH];
    char *mcro_line = NULL;
    size_t mcro_lines_size= 0;
    int flag = 0; /*Indicates inside the macro*/


    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       fprintf(stderr,"FILE ERROR: Failed to open file");
       exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
           Split result = split_line(line);
           if (strncmp(line, "mcro", 4) == 0 && strncmp(result.part1, "mcroend", 7) != 0){
               if (checking_mcro_name(result) == TRUE) {
                   flag = 1;
                   strcpy(mcro_names,line + 4);
                   mcro_names[strcspn(mcro_names, "\n")] = '\0';
                   Subtracting_spaces(mcro_names);
                   //printf("%s%s", mcro_names, mcro_line);
                   mcro_lines_size = 0 ;
                   free(mcro_line);
                   mcro_line = NULL;
               }
               else{
                   exit(EXIT_FAILURE);
               }
           }
           else if (flag && strncmp(line, "mcroend", 7) == 0){
                 flag = 0;
                 if (mcro_line != NULL) {
                     saving_mcro_data(mcro_names, mcro_line);
                 }
                 else {
                     saving_mcro_data(mcro_names, "");
                 }
                 free(mcro_line);
                 mcro_line = NULL;
           }
           else if (flag == 1){
                 size_t line_length = strlen(line);
                 char *new_mcro_lines = realloc(mcro_line,mcro_lines_size + line_length + 1);
                 if (new_mcro_lines == NULL) {
                     fprintf(stderr,"MEMORY ERROR: allocation failed - mcro lines");
                     exit(EXIT_FAILURE);
                 }
                 mcro_line = new_mcro_lines;
                 strcpy(mcro_line + mcro_lines_size, line);
                 mcro_lines_size = mcro_lines_size + line_length;
           }
    }
    free(mcro_line);
    fclose(file);
}

/* The function receives a pointer to the beginning of the line and divides it into 4 parts. */
Split split_line(char *line) {
    char line_copy [MAX_LINE_LENGTH];
    static Split split_copy_line;
    static char part1[MAX_LINE_LENGTH], part2[MAX_LINE_LENGTH], part3[MAX_LINE_LENGTH], part4[MAX_LINE_LENGTH];
    strcpy(line_copy, line);
    line_copy[strcspn(line_copy, "\n")] = '\0';

    char *token1 = strtok(line_copy, " ");
    char *token2 = strtok(NULL, " ");
    char *token3 = strtok(NULL, " ");
    char *token4 = strtok(NULL, "");

    if (token1 != NULL) {
        strcpy(part1, token1);
        split_copy_line.part1 = part1;
    }
    else  split_copy_line.part1 = NULL;
    if (token2 != NULL) {
        strcpy(part2, token2);
        split_copy_line.part2 = part2;
    }
    else  split_copy_line.part2 = NULL;
    if (token3 != NULL) {
        strcpy(part3, token3);
        split_copy_line.part3 = part3;
    }
    else  split_copy_line.part3 = NULL;
    if (token4 != NULL) {
        strcpy(part4, token4);
        split_copy_line.part4 = part4;
    }
    else  split_copy_line.part4 = NULL;
    return split_copy_line;
}

/* Checking the validity of the macro name */
int checking_mcro_name(Split split_copy_line) {
    int i;
    if (strncmp(split_copy_line.part1, "mcro", 4) == 0) {
        printf("%s\n", "1");
        if (split_copy_line.part2 == NULL) {
            printf("%s\n","Invalid macro name");
            printf("%s\n", "1");
            exit(EXIT_FAILURE);
            return FALSE;
        }
    }

    if (strncmp(split_copy_line.part1, "mcro", 4) == 0) {
        for (i=0; i < number_of_mcros; i++) {
            if (strcmp(split_copy_line.part2, mcros[i].mcro_name) == 0) {
                printf("%s\n","Invalid macro name");
                printf("%s\n", "new");
                exit(EXIT_FAILURE);
            }
        }
    }

    if (strcmp(split_copy_line.part1, "mcro") != 0 ) {
        printf("%s\n", "2");
        if ((strcmp(split_copy_line.part2, "mcro") == 0) || (strcmp(split_copy_line.part3, "mcro") == 0) || (strcmp(split_copy_line.part4, "mcro") == 0)){
            printf("%s\n","Invalid macro name");
            exit(EXIT_FAILURE);
        }
    }

    if (split_copy_line.part2!=NULL && split_copy_line.part3!=NULL){
            printf("%s\n", "3");
            printf("%s\n","Invalid macro name");
            exit(EXIT_FAILURE);
            return FALSE;
    }

    for (i = 0; i<NUM_INSRUCTION; i++) {
        if (strcmp(table_instruction[i].instruction_name,split_copy_line.part2) == 0) {
            printf("%s\n", "4");
            printf("%s\n","Invalid macro name");
            fflush(stdout);
            exit(EXIT_FAILURE);
            return FALSE;
        }
    }

    if (checking_register(split_copy_line.part2) == TRUE) {
        printf("%s\n","Invalid macro name");
        exit(EXIT_FAILURE);
    }

    if ((strcmp(split_copy_line.part2,"data") == 0) || (strcmp(split_copy_line.part2,"string") == 0) || (strcmp(split_copy_line.part2,"entry") == 0)||(strcmp(split_copy_line.part2,"extern") == 0)){
        printf("%s\n", "5");
        printf("%s\n","Invalid macro name");
        exit(EXIT_FAILURE);
    }

    char *p = split_copy_line.part2;
    i = 0;
    while (p[i] != '\0'){
           if ((isalnum(p[i]) == TRUE)|| (p[i] == '_')) {
               printf("%s\n", "ok");
               i++;
           }
           else {
                 printf("%s\n", "basa");
                 printf("%s\n","Invalid macro name");
                 exit(EXIT_FAILURE);
           }
    }
     return TRUE;
}

/* Creating a new file after deploying macros */
void create_file_am(char *inputfile, char *outputfile) {
  FILE *file_as;
  FILE *file_am;
  int flag = 0;

  char full_filename_as[16] = {0};
  char full_filename_am[16] = {0};
  char line_of_file[MAX_LINE_LENGTH];

  memcpy(full_filename_as, inputfile, strlen(inputfile));
  strcat(full_filename_as ,".as");
  file_as = fopen(inputfile, "r");

  memcpy(full_filename_am, outputfile, strlen(outputfile));
  strcat(full_filename_am ,".am");
  file_am = fopen(outputfile, "w");

  if (file_as == NULL || file_am == NULL) {
      fprintf(stderr,"FILE ERROR: Failed to open file");
      exit(EXIT_FAILURE);
  }
  while(fgets(line_of_file, sizeof(line_of_file), file_as) != NULL){
        Split result = split_line(line_of_file);
        //printf("%s\n",result.part1);

        if (strncmp(result.part1, "mcroend", 7) == 0) {
          flag = 0;
          continue;
        }

        if (strncmp(result.part1, "mcro", 4) == 0) {
            flag = 1;
            continue;
        }

       if (flag == 1) {
           continue;
       }
        Subtracting_spaces(result.part1);
        char *mcro_lines = replacing_mcro_name(result.part1);
        if (mcro_lines != NULL) {
            //printf("%s",mcro_lines);
            fputs(mcro_lines, file_am);
            continue;
        }

        fputs(line_of_file, file_am);
  }
  fclose(file_as);
  fclose(file_am);
}

/* Release of pointers */
void release_memory(){
    int i;
    for (i = 0; i<number_of_mcros; i++){
         free(mcros[i].mcro_name);
         free(mcros[i].mcro_lines);
    }
    free(mcros);
}

/* Removing spaces from the beginning of a word. */
void Subtracting_spaces(char *string) {
    int i = 0;
    while (isspace((unsigned char)string[i])) {
        i++;
    }
    if (i > 0) {
        memmove(string, string + i,strlen(string)- i + 1);
    }
    //printf("%s\n",string);
}

/* Line length check. */
/*int line_length(char *line) {
    int count = 0;
    while (*(line)!= '\n') {
        line++;
        count++;
    }
    if (count > 80) {
        return FALSE;
    }
    return TRUE;
}*/


/*Register integrity check*/
int checking_register(char *x) {
    char i;
    if (strlen(x) == 2){
        if ((*x) == 'r') {
            for (i= '0'; i < '8'; i++) {
                 if (*(x + 1) == i ) {
                         return TRUE;
                 }
            }
        }
    }
   return FALSE;
}