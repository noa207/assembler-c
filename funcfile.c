#include "assembler.h"
/*
int main(int argc, char *argv[]) {
  FILE *file;
  FILE *file2;
  char line_of_file[MAX_LINE_LENGTH] = {0};
  char **tokens;
  int n = 15;
  int i = 0;
  char full_filename[16] = {0};
  char full_filename2[16] = {0};
  strcpy(full_filename, create_fullname_of_file(argv[1], "as"));
  strcpy(full_filename2, create_fullname_of_file(argv[1], "am"));
  if(!(file_handling_of_reading(full_filename, &file))){
    printf("no\n");
  }
  if(!(file_handling_of_writing(full_filename2, &file2))){
    printf("basa\n");
  }
  printf("full name %s\n", full_filename);
  printf("full name2 %s\n", full_filename2);
  while (fgets(line_of_file, sizeof(line_of_file), file) != NULL){
    tokens = split_line(line_of_file);
    while (tokens[i] != NULL) {
        printf("Word %d: %s\n", i + 1, tokens[i]);
        i++;
    }
    free(tokens);
  }
  
  return 1;
}
*/



/* This function create full name of the file with extension
    input:
      filename- the name of the file name we want create 
      file_type- the type of the file we want to create its fullname
    output:
      return filename with extension
*/
char *create_fullname_of_file(char *filename, char *file_type){
  char *full_filename = (char *)malloc(strlen(filename));
  if(full_filename == NULL){
    fprintf(stderr, "MEMORY ERROR: memory allocation is faild\n");
    return NULL;
  }
  memcpy(full_filename, filename, strlen(filename));
  strcat(full_filename, ".");
  strcat(full_filename, file_type);
  return full_filename;
}


/* This function check if we can read  from file
    input:
      filename- the name of the file we want to read
      file- the file we try to read, it's a pointer
    output:
      return FALSE if the file is not open for reading else TRUE
*/
boolean file_handling_of_reading(char *filename, FILE **file){ /*error if file does not exist or is not opened*/
  if((*file = fopen(filename, "r")) == NULL){
    fprintf(stderr,"FILE ERROR: the file %s could not open for reading\n", filename);
    return FALSE;
  }
  return TRUE;
}

/* This function check if we can write from file
    input:
      filename- the name of the file we want to write
      file- the file we try to write, it's a pointer
    output:
      return FALSE if the file is not open for writing else TRUE
*/
boolean file_handling_of_writing(char *filename, FILE **file){ /*error if file does not exist or is not opened*/
  if((*file = fopen(filename, "w")) == NULL){
    fprintf(stderr,"FILE ERROR: the file %s could not open for writing\n", filename);
    return FALSE;
  }
  return TRUE;
}

/* This function aplit line to array of words
    input:
      string_of_line- the line we want to split
    output:
      split_line_words- the array of words after we splitted
*/
char **split_line(char *string_of_line){
  int count_tokens = 0;
  char *line_copy;
  char *split_token;
  char **split_line_words = NULL;
  char *delimiter = " \t";
  string_of_line[strcspn(string_of_line, "\n")] = '\0';
  line_copy = (char *)malloc(strlen(string_of_line) + 1); 
  if( line_copy == NULL){
    fprintf(stderr, "MEMORY ERROR: memory allocation is faild\n");
    return NULL;
  }
  strcpy(line_copy, string_of_line);
  split_token = strtok(line_copy, delimiter);
  while(split_token != NULL){
    printf( " %s\n", split_token );
    
    split_line_words = realloc(split_line_words, (count_tokens + 1) * sizeof(char *));
    
    if(!split_line_words){
      fprintf(stderr, "MEMORY ERROR: memory allocation is faild\n");
      free(line_copy);
      return NULL;
    }
    split_line_words[count_tokens] = malloc(strlen(split_token) + 1);
    if(!split_line_words[count_tokens]){
      fprintf(stderr, "MEMORY ERROR: memory allocation is faild\n");
      free(line_copy);
      return NULL;
    }
    strcpy(split_line_words[count_tokens], split_token);
    split_line_words[count_tokens][strlen(split_token)] = '\0';
    count_tokens++;
    split_token = strtok(NULL, delimiter);
    
  }
  free(line_copy);
  return split_line_words;
}
/* This function check if the variable is not protected word
    input:
      variable- the variable name we want to check
    output:
      return FALSE if the name is protected name, else TRUE

*/
boolean check_not_protected_word(char *variable_name){
  char *protected_words[] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "data" , "string", "entry", "extern" , "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};
  while (protected_words[i] != NULL){
    if (strcmp(mcro_name, protected_words[i]) == 0) { /*check if is it protected word*/
      fprintf(stderr,"STRING ERROR:  %s Invalid macro name - name of instruction/ directive/ register\n", mcro_name);
      return FALSE;
    } else{
      i++:
    }
  }
  return TRUE;
}