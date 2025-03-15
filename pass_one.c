
int pass_one(char *filename){
  int IC = 100;
  int DC =0;
  FILE *file;
  boolean error = FALSE;
  char *full_filename = create_fullname__of_file(filename, "am");
  char line_of_file[MAX_LINE_LENGTH] = {0};
  file = fopen(filename, "r");
  while(fgets(line_of_file, sizeof(line_of_file),file) != NULL){
    if (string[0] == ';'){
      continue;
    }if (whitespace_sentence_vaild){


    }
  }
  if ()
  
}


  

boolean instruction_sentence_valid(char *string){

}

boolean directive_sentence_valid(char *string){

}

boolean whitespace_sentence_vaild(char *string){
  int i = 0;
  while(string[i] != '\n'){
    if(isspace(string[i])){
      i++;
    } else{
        return FALSE;
    }
  }
  return TRUE;
}

/* sentence to binary
*/

boolean directive_word_valid(char *word){
  int i = 0;
  char directive_words[4][6] ={".data", ".string", ".entry", ".extern"};
  if(word[0] != '.'){
    return FALSE;
  } else{
    for(i = 0; i < 4; i++){
      if(strcmp(directive_words[i], word +1))
        return TRUE;
    } 
  }
  return FALSE; 
}


char *directive_sentence_to_binary(char *line_string, ){

}
boolean validate_data_directive(char *string){

}

