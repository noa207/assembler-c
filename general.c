#include "general.h"

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
  char **temp_split_line_words = NULL;
  char *delimiter = " ";
  size_t length = strlen(string_of_line);

  if (length > 0 && (string_of_line[length - 1] == '\n' || string_of_line[length - 1] == '\r')) {
    string_of_line[length - 1] = '\0';
    length--;
  }
  if (length > 0 && (string_of_line[length - 1] == '\r')) {
    string_of_line[length - 1] = '\0';
  }

  line_copy = malloc(strlen(string_of_line) + 1);

  if( line_copy == NULL){
    fprintf(stderr, "MEMORY ERROR: memory allocation is faild\n");
    return NULL;
  }

  strcpy(line_copy, string_of_line);
  split_token = strtok(line_copy, delimiter);

  while(split_token != NULL){
    printf( " %s\n", split_token );

    temp_split_line_words = realloc(split_line_words, (count_tokens + 1) * sizeof(char *));

    if(!temp_split_line_words){
      fprintf(stderr, "ERROR: memory allocation is faild\n");
      free(line_copy);
      return NULL;
    }
    split_line_words = temp_split_line_words;

    split_line_words[count_tokens] = malloc(strlen(split_token) + 1);
    if(!split_line_words[count_tokens]){
      fprintf(stderr, "ERROR: memory allocation is faild\n");
      free(line_copy);
      free(split_line_words);
      return NULL;
    }

    strcpy(split_line_words[count_tokens], split_token);
    count_tokens++;
    split_token = strtok(NULL, delimiter);
  }

  split_line_words = realloc(split_line_words, (count_tokens + 1) * sizeof(char *));
  split_line_words[count_tokens] = NULL;
  free(line_copy);
  return split_line_words;
}

/* This function frees the memory allocated
   input:
      pointer to the beginning of the list
*/
void release_memory(char **tokens){
  int i = 0;
  for ( i = 0; tokens[i] != NULL; i++) {
    free(tokens[i]);
  }
  free(tokens);
}

/* This function check if the variable is not protected word
    input:
      variable- the variable name we want to check
    output:
      return FALSE if the name is protected name, else TRUE
*/
boolean check_not_protected_word(char *variable_name){
  int i = 0;
  char *protected_words[] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "data" , "string", "entry", "extern" , "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7"};

  if (!variable_name) {
    fprintf(stderr, "ERROR: check_not_protected_word received NULL pointer\n");
    return FALSE;
  }
  for (i = 0; i < NUM_PROTECTED_WORDS; i++) {
    if (strcmp(variable_name, protected_words[i]) == 0) { /* Compare against protected words */
      fprintf(stderr, "STRING ERROR: %s Invalid macro name - name of instruction/directive/register\n", variable_name);
      return FALSE;
    }
  }
  return TRUE;
}

/* This function ger a pointer to string and removes unnecessary spaces
input:
    line - line from the file
*/
/* this function was taken from mmn 22 and was divided by void read_comp_parsing(char *command)*/
void clean_spaces (char *line) {
    char *end;
    /*Trim spaces*/
    while (*line == ' ') line++;

    /*Remove spaces*/
    end = line + strlen(line) - 1;
    while (end > line && isspace(*end)) {
        *end-- = '\0';
    }
}
