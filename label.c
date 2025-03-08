#include "assembler.h"
struct label{
    char *label_name;
    int label_address;
    char *label_character;
}
boolean check_is_label_valid(char *label){
    int i = 0;
    while(label[i] != '\0'){
      if(isupper(label[i])){
        i++;
      } else{
        return FALSE;
      }
    }
    return TRUE;
}




