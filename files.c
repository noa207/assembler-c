#include "files.h"

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
