#include "assembler.h"

/*find good place for them*/
Mcro *mcros = NULL;
/*int number_of_mcros = 0;*/


/* This function implement the pre process of the assembler
    input:
      filename- the name of the file we work with
    output:
      if this process going well it will continue to the next pass, else finish to work with this file
*/
int pre_process(char *filename) {
  FILE *file;
  /*char **tokens;*/
  int line_counter = 0;
  char *full_filename_as = (char *)malloc(strlen(filename) + 4); /*allocate memory for the fullname as file*/
  char *full_filename_am = (char *)malloc(strlen(filename) + 4); /*allocate memory for the fullname am file*/
  char line_of_file[MAX_LINE_LENGTH] = {0};
  char mcro_name_variable[MAX_LINE_LENGTH] = {0};
  char *mcro_line = NULL;
  size_t mcro_lines_size = 0;
  int flag = 0; /*Indicates inside the macro- needs to be more detailed*/
  int error_flag = 0;
  char *new_mcro_lines;
  size_t line_length;
  int number_of_mcros = 0;
  strcpy(full_filename_as, create_fullname_of_file(filename, "as")); /*create fullname for the file as */
  strcpy(full_filename_am, create_fullname_of_file(filename, "am")); /*create fullname for the file am */
  if(!(file_handling_of_reading(full_filename_as, &file))){ /*check if we can open the as file*/
    error_flag = 1;
  } else{
  while (fgets(line_of_file, sizeof(line_of_file), file) != NULL){ /*read each line in the file*/

    /*tokens = split_line(line_of_file);*/
    Subtracting_spaces(line_of_file);
    if (strncmp(line_of_file, "mcro", 4) == 0 &&  strncmp(line_of_file, "mcroend", 7) != 0){
        *(line_of_file + 4);
        printf("new string %s\n", line_of_file);
        Subtracting_spaces(line_of_file);
        if (checking_mcro_name(word_split(line_of_file)) && whitspace_line(*(line_of_file + strlen(word_split(line_of_file ,' '))))) { /*check if is macro name of the define valid and there is no other words after it*/
          flag = 1;
          strcpy(mcro_name_variable,line_of_file + 4); /* pointer to the part after the word mcro for his name */
          mcro_name_variable[strcspn(mcro_name_variable, "\n")] = '\0';
          Subtracting_spaces(mcro_name_variable);/* save the name without spaces before it */
          mcro_lines_size = 0 ;
          /*free(mcro_line);*/
          mcro_line = NULL;
        }
    } else if (strstr(line_of_file, " mcro ") != NULL || strstr(line_of_file, " macroend ") != NULL){ /*check if there is words before define mcro*/
      error_flag = 1;
      fprintf(stderr,"[%d] STRING ERROR: Unwanted chars before mcro or mcroend\n", line_counter);     
    } else if (flag && strncmp(line_of_file, "mcroend", 7) == 0){ /*check the macro name of the define and there is no other words after it*/
      *(line_of_file + 7);
      Subtracting_spaces(line_of_file);
      if (whitspace_line(*(line_of_file + strlen(word_split(line_of_file, ' '))))){
        flag = 0;
        if (mcro_line != NULL) {
          saving_mcro_data(mcro_name_variable, mcro_line, number_of_mcros);
        }
        else {
          saving_mcro_data(mcro_name_variable, "", number_of_mcros);
        }
        free(mcro_line);
        mcro_line = NULL;
      }
    }
    else if (flag == 1){ /*what this flag does?*/
      line_length = strlen(line_of_file);
      new_mcro_lines = realloc(mcro_line, mcro_lines_size + line_length + 1);
      if (new_mcro_lines == NULL) {
        error_flag = 1;
        fprintf(stderr,"[%d] MEMORY ERROR: allocation failed - mcro lines",line_counter);
      }
      mcro_line = new_mcro_lines;
      strcpy(mcro_line + mcro_lines_size, line_of_file);
      mcro_lines_size = mcro_lines_size + line_length;
    }
    line_counter++;         
  }
  }
  if(error_flag == 0){ /*check if were errors while we read the file, if error_flag is zero its means the as file is ok*/
    create_am_file(full_filename_as, full_filename_am);
  } else{
    return 1;
  }
  /*release_memory();*/ /*shos errors*/
  free(full_filename_as);
  free(full_filename_am);
  
  free(mcro_line);
  fclose(file);
  return 0;
}

/* This function create am file from as file
    input:
      full_filename_as- the name of the file we read from it, source file
      full_filename_am- the name of the file we write to him, destination file
    output:
      if this process going well it will continue to the next pass, else finish to work with this file
*/
void create_am_file(char *input_filename, char *output_filename){
  FILE *file_input;
  FILE *file_output;
  int flag = 0;
  /*char **tokens;*/
  char line_of_file[MAX_LINE_LENGTH] = {0};
  char *mcro_lines;
  int count_replacements = 0;
  if(!(file_handling_of_reading(input_filename, &file_input))){
    exit(0);
  }
  if(!(file_handling_of_writing(output_filename, &file_output))){
    exit(0);
  }
  while(fgets(line_of_file, sizeof(line_of_file), file_input) != NULL){
    if (strncmp(line_of_file, "mcroend", 7) == 0) {
      flag = 0;
      continue;
    }

    if (strncmp(line_of_file, "mcro", 4) == 0) { /*what is that?*/
        flag = 1;
        continue;
    }

    if (flag == 1) { /*what is that?*/
        continue;
    }
    Subtracting_spaces(line_of_file); /*need to change*/

    mcro_lines = replacing_mcro_name(word_split(line_of_file, ' '), count_replacements);/*need to change*/
    count_replacements++;
    if (mcro_lines != NULL) {
        fputs(mcro_lines, file_output);
        continue;
    }
    fputs(line_of_file, file_output);
}
  fclose(file_input);
  fclose(file_output);
}

/* This function get the index of the mcro define in line
    input:
      array_of_line- the line after we split to array of strings
      mcro_name- the define of mcro / mcroend
    output:
      return the index of the mcro define in the line
*/
int get_index_of_mcro(char **array_of_line, char *mcro_define){
  int i = 0;
  while (array_of_line[i] != NULL) {
    if(strcmp(array_of_line[i], mcro_define) == 0){
      return i;
    }
  }
  return -1;  
}

/* This function check if the line of define mcro is correct 
    input:
      array_of_line- the line after we split to array of strings
      count- the number of the words we excpet to be in line
    output:
      return FALSE if the line is not valid and has more then count words number else TRUE
*/
boolean mcro_line_valid(char **array_of_line, int count){
  if(array_of_line[count] != NULL){
    return FALSE;
  } else{
    return TRUE;
  }
}

/* This function check if if the mcro name is valid 
    input:
      mcro_name- the mcro name we want to check
    output:
      return FALSE if the name is not valid for mcro define else TRUE
*/
boolean checking_mcro_name(char *mcro_name) {
  
  int i = 0;
  if(strlen(mcro_name) > 31){
    return FALSE;
  }
  if (mcro_name == NULL) {
    fprintf(stderr,"STRING ERROR:  %s Invalid macro name - not exist\n", mcro_name);
    return FALSE;
  }
  if (macro_array_scan(mcro_name) == 0) {
      fprintf(stderr,"STRING ERROR:  %s Invalid macro name - already exist\n", mcro_name);
      return FALSE;
  }
  if (!check_not_protected_word(mcro_name)){
    return FALSE;
  }
  char *p = mcro_name; /*not sure its ok*/
  i = 0;
  while (p[i] != '\0'){
    if ((isalnum(p[i])) || (p[i] == '_')) { /*check if its chars are correct*/
      i++;
      }
    else {
        fprintf(stderr,"STRING ERROR:  %s Invalid macro name- unwanted chars\n", mcro_name);
        return FALSE;
      }
  }
  return TRUE;
}

/* The function receives a pointer to a name and checks whether the name is in the macro array, if so, replaces the line with the macro value. ֿֿ*/
char *replacing_mcro_name(char *mcro_name, int number_of_mcros) {
  int i;
  for (i = 0; i<number_of_mcros ; i++) {
       if (strcmp(mcros[i].mcro_name, mcro_name) == 0) {
           return mcros[i].mcro_lines;
       }
       /*printf("%s%s", mcros[i].mcro_name, mcros[i].mcro_lines);*/
  }
  return NULL;
}

/* Removing spaces from the beginning of a word. */
void Subtracting_spaces(char *string) {
  int i = 0;
  while (isspace((unsigned char)string[i])) {
      i++;
  }
  if (i > 0) {
      memmove(string, string + i,strlen(string) - i + 1);
  }
  
}

/*i need explain how its work*/

/* Storing the name and content of the macros in the dynamic array */
void saving_mcro_data(char *mcro_name, char *mcro_lines, int number_of_mcros) {
  Mcro *new_mcros = realloc(mcros,(number_of_mcros + 1) * sizeof(Mcro));
  if (new_mcros == NULL) {
      fprintf(stderr,"MEMORY ERROR: allocation failed");
      /*exit(EXIT_FAILURE);*/
      return;
  }
  mcros = new_mcros;

  /* Allocating memory for the macro name and store */
  mcros[number_of_mcros].mcro_name = malloc(strlen(mcro_name) + 1);
  if (mcros[number_of_mcros].mcro_name == NULL) {
      fprintf(stderr,"MEMORY ERROR: allocation failed - mcro name");
      /*exit(EXIT_FAILURE);*/
      return;
  }
  strcpy(mcros[number_of_mcros].mcro_name, mcro_name);

  /* Allocating memory for the macro content and store */
  mcros[number_of_mcros].mcro_lines = malloc(strlen(mcro_lines) + 1);
  if (mcros[number_of_mcros].mcro_lines == NULL) {
      fprintf(stderr,"MEMORY ERROR: allocation failed - mcro lines");
      /*exit(EXIT_FAILURE);*/
      return;
  }
  strcpy(mcros[number_of_mcros].mcro_lines, mcro_lines);
  number_of_mcros++;
}

/*why does you use it?*/
/* Release of pointers */
/*
void release_memory(int number_of_mcros) {
  int i;
  for (i = 0; i<number_of_mcros; i++){
       free(mcros[i].mcro_name);
       free(mcros[i].mcro_lines);
       i++;
  }
  free(mcros);
}*/

boolean macro_array_scan( char *string){
  int i = 0;
  char *p = mcros[i].mcro_name;
  while (p[i] != '\0'){
      if (strcmp(string, mcros[i].mcro_name) == 0) {
          return FALSE;
      }
      i++;
  }
  return TRUE;
}


char *word_split(char *string, char delimiter){
  char *split_token;
  split_token = strtok(string, delimiter);
  return split_token;

}


boolean whitspace_line(char *string){
  int i = 0;
  while(string[i] != '\0'){
    if(!isspace(string[i])){
      return FALSE;
    }
    i++;
  }
  return TRUE;
}

