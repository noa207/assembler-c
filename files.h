#ifndef FILES_H
#define FILES_H

#include "general.h"

/* This function create full name of the file with extension
    input:
      filename- the name of the file name we want create
      file_type- the type of the file we want to create its fullname
    output:
      return filename with extension
*/
char *create_fullname_of_file(char *filename, char *file_type);

/* This function check if we can read  from file
    input:
      filename- the name of the file we want to read
      file- the file we try to read, it's a pointer
    output:
      return FALSE if the file is not open for reading else TRUE
*/
boolean file_handling_of_reading(char *filename, FILE **file);

/* This function check if we can write from file
    input:
      filename- the name of the file we want to write
      file- the file we try to write, it's a pointer
    output:
      return FALSE if the file is not open for writing else TRUE
*/
boolean file_handling_of_writing(char *filename, FILE **file);


#endif
