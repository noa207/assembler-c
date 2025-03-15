#include "assembler.h"

int main(int argc, char *argv[]){ 
  check_file(argc, argv);
  create_file("hello","as");
  append_line_to_file("hello world", "hello.as");
  return 0;
}

/* This function check if does file exist
    input:
      argc- argument count, integer variable which contain the number of command line arguments
      argv- argument vector, char array pointers variable of list all arguments
*/
void check_file(int argc, char *argv[]){
  int i = 0;
  FILE *file; 
  char filename[16] = {0};
  char **file_names_list = (char**)malloc(argc*sizeof(char*));
  if (argc < 2) { /*error if argument does not exist*/
      fprintf(stderr,"FILE ERROR: No filename argument provided.\n"); 
    }
  for (i = 1; i < argc; i++){
    memcpy(filename, argv[i], strlen(argv[i]));
    strcat(filename ,".am");
    if((file = fopen(filename, "r"))  == NULL){ /*error if file does not exist or is not opened*/
      perror("FILE ERROR"); 
   } else {
      read_file_line(filename);
      file_names_list[i] = filename;
    }
    memset(filename, 0, sizeof(filename));
  }
}

/* This function read each line from file 
    input:
      filename- the name of the file we want to read
*/
void read_file_line(char *filename) {
  FILE *file;
  char line_of_file[256] = {0};
  file = fopen(filename, "r");
  while(fgets(line_of_file, sizeof(line_of_file),file) != NULL){
      printf("line of file %s : %s\n", filename,line_of_file);
    }
}

/* This function create new file 
    input:
      file_name- the name of the file we want to create
      file_type- the type of the file we want to create
*/
void create_file(char *file_name, char *file_type){
  FILE *file;
  char full_filename[16] = {0};
  memcpy(full_filename, file_name, strlen(file_name));
  strcat(full_filename, ".");
  strcat(full_filename, file_type);
  file = fopen(full_filename, "w");
  fclose(file);
}

char *create_fullname__of_file(char *file_name, char *file_type){
  char full_filename = (char *)malloc(strlen(file_name));
  strcpy(full_filename, file_name, strlen(file_name));
  strcat(full_filename, ".");
  strcat(full_filename, file_type);
  return *full_filename;
}
/* This function append line to new file 
    input:
      line_string- the line we want to append to the file
      full_file_name- the name of file with the type file
*/
void append_line_to_file(char *line_string, char *full_file_name){
  FILE *file;
  file = fopen(full_file_name, "a");
  if(fputs(line_string, file) == EOF){
    fprintf(stderr,"FILE ERROR: Failed to append to file");
  }
  fclose(file);
}