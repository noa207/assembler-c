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

 /* Dynamically allocated array for Mcros */
MacrosArray mcro_array;

 int pre_process(char *filename) {
    FILE *file_input;
    FILE *file_output;

    char **tokens;
    char *full_filename_as = (char *)malloc(strlen(filename) + 4);/*allocate memory for the fullname as file*/
    char *full_filename_am = (char *)malloc(strlen(filename) + 4);/*allocate memory for the fullname am file*/
    char line_of_file[MAX_LINE_LENGTH] = {0};/* array of line of file*/
    char mcro_names[MAX_LINE_LENGTH] = {0};/*array of mcro name */
    char *mcro_line = NULL;/* pointer to macro line*/
    char *macro_replacement;/* pointer to the macro content*/
    char *new_mcro_lines;/* pointer to new macro line*/
    int flag = 0;/* symbolizes whether we are in the macro content */
    int error_flag = 0;/* indicates whether there is an error */
    size_t len;/* the length of the line*/
    size_t mcro_lines_size = 0;/* the length of the mcro line*/

    if (!full_filename_as || !full_filename_am) {
        fprintf(stdout, "ERROR: Memory allocation failed\n");
        return 1;
    }

    strcpy(full_filename_as, create_fullname_of_file(filename, "as"));/*create fullname for the file as */
    strcpy(full_filename_am, create_fullname_of_file(filename, "am"));/*create fullname for the file am */

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

        /* check line for "mcro" start */
        if (tokens[0] && strcmp(tokens[0], "mcro") == 0) {
            if (tokens[1] && mcro_name_checking(tokens[1]) && mcro_line_valid(tokens, 2)) {
                flag = 1;
                strcpy(mcro_names, tokens[1]);
                mcro_names[strcspn(mcro_names, "\n")] = '\0';
                clean_spaces(mcro_names);
                mcro_lines_size = 0;
                free(mcro_line);
                mcro_line = NULL;
                continue;
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

         /* check line for "mcroend" */
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

        /* inside a macro definition */
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

        /* copy line from input file to output .am file */
        if (flag == 0) {

        	/* skip empty lines (only whitespace or `\n`) */
        	char *trimmed_line = line_of_file;
        	while (*trimmed_line && isspace((unsigned char)*trimmed_line)) {
            	trimmed_line++;  /* Move past whitespace */
        	}
        	if (*trimmed_line == '\0') {
            	continue;  /* skip writing this line */
        	}

            /* ensure the line has a newline before writing */
        	len = strlen(line_of_file);
        	if (len > 0 && line_of_file[len - 1] != '\n') {
            	strcat(line_of_file, "\n");  /* append newline if missing */
        	}

            macro_replacement = mcro_insert_data(tokens[0]);

            /* if the line is macro name, then replace it with macro content */
            if (macro_replacement != NULL) {
                fputs(macro_replacement, file_output);  /* replace the macro */
            } else {
                fputs(line_of_file, file_output);
            }
        }
        release_memory(tokens);
    }

    /* if error in input file, then remove output file */
    if (error_flag == 1) {
        remove(full_filename_am);
        mcro_memory_release();
        return 1;
    }

    free(full_filename_as);
    free(full_filename_am);
    free(mcro_line);
    fclose(file_input);
    fclose(file_output);
    return 0; /* if no errors in input file processing */
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

   if (!mcro_array_scan_result(mcro_name)){
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
   for (i = 0; i< mcro_array.number_of_mcros; i++) {
        if (strcmp(mcro_array.mcros[i].mcro_name, mcro_name) == 0) {
            return (mcro_array.mcros[i].mcro_lines);
        }
   }
   return NULL;
 }

 /* Storing the name and content of the macros in the dynamic array */
 void mcro_data_saving(char *mcro_name, char *mcro_lines) {
   size_t len;
   Mcro *new_mcros = realloc(mcro_array.mcros,(mcro_array.number_of_mcros + 1) * sizeof(Mcro));
   if (new_mcros == NULL) {
       fprintf(stdout,"ERROR: memory allocation failed");
       exit(EXIT_FAILURE);
   }
   mcro_array.mcros = new_mcros;

   /* allocating memory for the macro name and store */
   mcro_array.mcros[mcro_array.number_of_mcros].mcro_name = malloc(strlen(mcro_name) + 1);
   if (mcro_array.mcros[mcro_array.number_of_mcros].mcro_name == NULL) {
       fprintf(stdout,"ERROR:  memory allocation failed - mcro name");
       exit(EXIT_FAILURE);
   }
   strcpy(mcro_array.mcros[mcro_array.number_of_mcros].mcro_name, mcro_name);

   /* allocating memory for the macro content and store */
   mcro_array.mcros[mcro_array.number_of_mcros].mcro_lines = malloc(strlen(mcro_lines) + 1);
   if (mcro_array.mcros[mcro_array.number_of_mcros].mcro_lines == NULL) {
       fprintf(stdout,"ERROR: memory allocation failed - mcro lines");
       exit(EXIT_FAILURE);
   }
   strcpy(mcro_array.mcros[mcro_array.number_of_mcros].mcro_lines, mcro_lines);
   len = strlen(mcro_lines);
    if (len > 0 && mcro_lines[len - 1] != '\n') {
        strcat(mcro_array.mcros[mcro_array.number_of_mcros].mcro_lines, "\n");  /*append newline if missing*/
    }
   mcro_array.number_of_mcros++;
 }


/* This function frees the memory allocated of mcro array
   input:
      pointer to the beginning of the array
*/
void mcro_memory_release(void){
   int i;
   for (i = 0; i<mcro_array.number_of_mcros; i++){
        free(mcro_array.mcros[i].mcro_name);
        free(mcro_array.mcros[i].mcro_lines);
   }
   free(mcro_array.mcros);
 }


/* The function goes through the array and checks if the string is equal to one of the macro names
   input:
     string -  the string we want compare to all the macro names in the array
   output:
     return true is the word does not exist otherwise false
 */
boolean mcro_array_scan_result(char *string) {
 int i = 0;
 for (i = 0 ; i < mcro_array.number_of_mcros; i++){
  if (strcmp(string, mcro_array.mcros[i].mcro_name) == 0) {
    fprintf(stderr,"ERROR:  %s Invalid macro name - already exist\n", string);
     return FALSE;
  }
 }
 return TRUE;
}

