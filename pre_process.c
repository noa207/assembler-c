#include "pre_process.h"

 /* This function implement the pre process of the assembler
     Input:
       	filename - the name of the input file to process
     Output:
		creates .am output file with macro replacements
	 Return:
       	'0' if no issues with input file processing
	   	'1' if there was an error in input file processing
 */
 int pre_process(char *filename) {
    FILE *file_input;
    FILE *file_output;

    char **tokens;
    char *full_filename_as = (char *)malloc(strlen(filename) + 4);
    char *full_filename_am = (char *)malloc(strlen(filename) + 4);
    char line_of_file[MAX_LINE_LENGTH] = {0};/* array of line of file*/
    char mcro_names[MAX_LINE_LENGTH] = {0};/*array of mcro name */
    char *mcro_line = NULL; /* pointer to macro line*/
    char *macro_replacement; /* pointer to the macro content*/
    char *new_mcro_lines; /* pointer to new macro line*/
    int flag = 0; /* symbolizes whether we are in the macro content */
    int error_flag = 0; /* indicates whether there is an error */
    size_t len; /* the length of the line*/
    size_t mcro_lines_size = 0; /* the length of the mcro line*/

<<<<<<< HEAD
/* This function implement the pre process of the assembler
    input:
      filename- the name of the file we work with
    output:
      if this process going well it will continue to the next pass, else finish to work with this file
*/
int pre_process(char *filename) {
  FILE *file;
  char **tokens;
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

      tokens = split_line(line_of_file);
      Subtracting_spaces(line_of_file);
      if (strncmp(line_of_file, "mcro", 4) == 0 &&  strncmp(line_of_file, "mcroend", 7) != 0){
          /**(line_of_file + 4);
          printf("new string %s\n", line_of_file);
          Subtracting_spaces(line_of_file);*/
          if (checking_mcro_name(tokens[1]) && mcro_line_valid(tokens, 2)) { /*check if is macro name of the define valid and there is no other words after it*/
            flag = 1;
            strcpy(mcro_name_variable,tokens[1]); /* pointer to the part after the word mcro for his name */
            mcro_name_variable[strcspn(mcro_name_variable, "\n")] = '\0';
            Subtracting_spaces(mcro_name_variable);/* save the name without spaces before it */
            mcro_lines_size = 0 ;
            /*free(mcro_line);*/
            mcro_line = NULL;
          }
      } if (get_index_of_mcro(tokens, "mcro") > 0){ /*check if there is words before define mcro*/
        error_flag = 1;
        fprintf(stderr,"STRING ERROR: Unwanted chars before mcro\n");     
      } else if (flag && strncmp(line_of_file, "mcroend", 7) == 0 && mcro_line_valid(tokens, 1)){ /*check the macro name of the define and there is no other words after it*/
          flag = 0;
          if (mcro_line != NULL) {
            saving_mcro_data(mcro_name_variable, mcro_line, number_of_mcros);
          }
          else {
            saving_mcro_data(mcro_name_variable, "", number_of_mcros);
          }
          free(mcro_line);
          mcro_line = NULL;
      } else if (flag == 1){ /*what this flag does?*/
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
    }
    line_counter++;         
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
  char **tokens;
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
    tokens = split_line(line_of_file);
    if (strncmp(line_of_file, "mcroend", 7) == 0) {
      flag = 0;
      continue;
=======
    if (!full_filename_as || !full_filename_am) {
        fprintf(stdout, "ERROR: Memory allocation failed\n");
        return 1;
    }

    strcpy(full_filename_as, create_fullname_of_file(filename, "as"));
    strcpy(full_filename_am, create_fullname_of_file(filename, "am"));

    if (!(file_handling_of_reading(full_filename_as, &file_input))) {
        fprintf(stdout, "ERROR: Unable to open input file %s\n", full_filename_as);
        return 1;
    }

    if (!(file_handling_of_writing(full_filename_am, &file_output))) {
        fprintf(stdout, "ERROR: Unable to open output file %s\n", full_filename_am);
		return 1;
    }

    /* Read line from input file */
    while (fgets(line_of_file, sizeof(line_of_file), file_input) != NULL) {
        tokens = split_line(line_of_file);

        if (mcro_get_index(tokens, "mcro") > 0){ /*check if there is words before define mcro*/
          error_flag = 1;
          fprintf(stdout,"ERROR: Unwanted chars before mcro\n");
        }

        /* Check line for "mcro" start */
        if (tokens[0] && strcmp(tokens[0], "mcro") == 0) {
            if (tokens[1] && mcro_name_checking(tokens[1]) && mcro_line_valid(tokens, 2)) {
                flag = 1;
                strcpy(mcro_names, tokens[1]);
                mcro_names[strcspn(mcro_names, "\n")] = '\0';
                Subtracting_spaces(mcro_names);
                mcro_lines_size = 0;
                free(mcro_line);
                mcro_line = NULL;
            } else {
                error_flag = 1;
                fprintf(stdout,"ERROR: First line of macro is not valid\n");
                continue;
            }
        }

        if (mcro_get_index(tokens, "mcroend") > 0  && strcmp(tokens[0], "mcroend") != 0){ /*check if there is words before define mcro*/
          error_flag = 1;
          fprintf(stdout,"ERROR: Unwanted chars before mcro\n");
        }

         /* Check line for "mcroend" */
         else if (flag && (strncmp(line_of_file, "mcroend", 7) == 0)){
           if (strcmp(tokens[0], "mcroend") == 0){
             flag = 0;
             if (!mcro_line_valid(tokens, 1)){
                error_flag = 1;
                fprintf(stdout,"ERROR: Last line of macro is not valid\n");
                continue;
             }
             if (mcro_line != NULL) {
                mcro_data_saving(mcro_names, mcro_line);
             } else {
                mcro_data_saving(mcro_names, "");
             }
             free(mcro_line);
             mcro_line = NULL;
             continue;
           }
         }

        /* Inside a macro definition */
        else if (flag == 1) {
            size_t line_length = strlen(line_of_file);
            new_mcro_lines = realloc(mcro_line, mcro_lines_size + line_length + 1);
            if (new_mcro_lines == NULL) {
                fprintf(stdout, "ERROR: Allocation new macro line failed\n");
                free(mcro_line);
                mcro_line = NULL;
                continue;
            }
            mcro_line = new_mcro_lines;
            strcpy(mcro_line + mcro_lines_size, line_of_file);
            mcro_lines_size += line_length;
            if (mcro_line[mcro_lines_size - 1] != '\n') {
               mcro_line[mcro_lines_size] = '\n';
               mcro_lines_size++;
            }
            mcro_line[mcro_lines_size] = '\0';
        }

        /* Copy line from input file to output .am file */
        if (flag == 0) {

        	/* Skip empty lines (only whitespace or `\n`) */
        	char *trimmed_line = line_of_file;
        	while (*trimmed_line && isspace((unsigned char)*trimmed_line)) {
            	trimmed_line++;  /* Move past whitespace */
        	}
        	if (*trimmed_line == '\0') {
            	continue;  /* Skip writing this line */
        	}

            /* Ensure the line has a newline before writing */
        	len = strlen(line_of_file);
        	if (len > 0 && line_of_file[len - 1] != '\n') {
            	strcat(line_of_file, "\n");  /*  Append newline if missing */
        	}

            macro_replacement = mcro_insert_data(tokens[0]);

            /* If the line is macro name, then replace it with macro content */
            if (macro_replacement != NULL) {
                fputs(macro_replacement, file_output);  /*  Replace the macro */
            } else {
                fputs(line_of_file, file_output);
            }
        }
        release_memory(tokens);
>>>>>>> d3374d4 (updating pre_process and h files)
    }

    /* If error in input file, then remove output file */
    if (error_flag == 1) {
        remove(full_filename_am);
        return 1;
    }

<<<<<<< HEAD
    if (flag == 1) { /*what is that?*/
        continue;
    }
    Subtracting_spaces(line_of_file); /*need to change*/

    mcro_lines = replacing_mcro_name(tokens[1], count_replacements);/*need to change*/
    count_replacements++;
    if (mcro_lines != NULL) {
        fputs(mcro_lines, file_output);
        continue;
    }
    fputs(line_of_file, file_output);
}
  fclose(file_input);
  fclose(file_output);
=======
    free(full_filename_as);
    free(full_filename_am);
    free(mcro_line);
    fclose(file_input);
    fclose(file_output);
    return 0; /* if no errors in input file processing */
>>>>>>> d3374d4 (updating pre_process and h files)
}

/* This function get the index of the mcro define in line
     input:
       array_of_line- the line after we split to array of strings
       mcro_name- the define of mcro / mcroend
     output:
       return the index of the mcro define in the line
 */
 int mcro_get_index(char **array_of_line, char *mcro_define){
   int i = 1;
   while (array_of_line[i] != NULL) {
     if(strcmp(array_of_line[i], mcro_define) == 0){
       return i;
     }
     i++;
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
 boolean mcro_name_checking(char *mcro_name) {
   int i = 0;
   char *p;
   if (mcro_name == NULL) {
     fprintf(stdout,"ERROR:  %s Invalid macro name - not exist\n", mcro_name);
     return FALSE;
   }
   if (strlen(mcro_name) > MAX_LENGTH_OF_MCRO_NAME){
     fprintf(stdout,"ERROR:  %s Invalid macro name - Invalid name \n", mcro_name);
     return FALSE;
   }
   if (mcro_array_scan_result(mcro_name) != TRUE){
     return FALSE;
   }
   if (!check_not_protected_word(mcro_name)){
     return FALSE;
   }
   p = mcro_name;
   i = 0;
   if(isalpha(p[0]) || p[0] == '_'){
     i++;
     while (p[i] != '\0'){
       if ((isalnum(p[i])) || (p[i] == '_')){ /*check if its chars are correct*/
         i++;
       }
       else {
         fprintf(stdout,"ERROR:  %s Invalid macro name- unwanted chars\n", mcro_name);
         return FALSE;
       }
     }
   }
   return TRUE;
 }

 /* The function receives a pointer to a name and checks whether the name is in the macro array, if so, replaces the line with the macro value. ֿֿ*/
 char *mcro_insert_data(char *mcro_name) {
   int i;
   for (i = 0; i< Macros_Array.number_of_mcros; i++) {
        if (strcmp(Macros_Array.mcros[i].mcro_name, mcro_name) == 0) {
            return (Macros_Array.mcros[i].mcro_lines);
        }
   }
   return NULL;
 }

 /* Storing the name and content of the macros in the dynamic array */
 void mcro_data_saving(char *mcro_name, char *mcro_lines) {
   size_t len;
   Mcro *new_mcros = realloc(Macros_Array.mcros,(Macros_Array.number_of_mcros + 1) * sizeof(Mcro));
   if (new_mcros == NULL) {
       fprintf(stdout,"ERROR: memory allocation failed");
       exit(EXIT_FAILURE);
   }
   Macros_Array.mcros = new_mcros;

   /* Allocating memory for the macro name and store */
   Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_name = malloc(strlen(mcro_name) + 1);
   if (Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_name == NULL) {
       fprintf(stdout,"ERROR:  memory allocation failed - mcro name");
       exit(EXIT_FAILURE);
   }
   strcpy(Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_name, mcro_name);

<<<<<<< HEAD
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



boolean whitspace_line(char *string){
  int i = 0;
  while(string[i] != '\0'){
    if(!isspace(string[i])){
      return FALSE;
=======
   /* Allocating memory for the macro content and store */
   Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_lines = malloc(strlen(mcro_lines) + 1);
   if (Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_lines == NULL) {
       fprintf(stdout,"ERROR: memory allocation failed - mcro lines");
       exit(EXIT_FAILURE);
   }
   strcpy(Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_lines, mcro_lines);
   len = strlen(mcro_lines);
    if (len > 0 && mcro_lines[len - 1] != '\n') {
        strcat(Macros_Array.mcros[Macros_Array.number_of_mcros].mcro_lines, "\n");  /*Append newline if missing*/
>>>>>>> d3374d4 (updating pre_process and h files)
    }
   Macros_Array.number_of_mcros++;
 }


/* frees the memory allocated of mcro array
   input:
      pointer to the beginning of the array
*/
/*void mcro_memory_release(){
   int i;
   for (i = 0; i<Macros_Array.number_of_mcros; i++){
        free(Macros_Array.mcros[i].mcro_name);
        free(Macros_Array.mcros[i].mcro_lines);
   }
   free(Macros_Array.mcros);
 }*/


/* The function goes through the array and checks if the string is equal to one of the macro names
   input:
     string -  the string we want compare to all the macro names in the array
   output:
     return true is the word does not exist otherwise false
 */
boolean mcro_array_scan_result(char *string) {
 int i = 0;
 for (i = 0 ; i < Macros_Array.number_of_mcros; i++){
  if (strcmp(string, Macros_Array.mcros[i].mcro_name) == 0) {
    fprintf(stderr,"ERROR:  %s Invalid macro name - already exist\n", string);
     return FALSE;
  }
 }
 return TRUE;
}

