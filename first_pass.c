#include "assembler.h"

boolean check_is_define_label_valid(char *label_name){
  int i = 0;
  /*if labal == instruction or labal == mcro*/
  if(strlen(label_name) > 31){
    return FALSE;
  } if(!isalpha(label_name[0])){
    return FALSE;
  } else{
    while(label_name[i] != '\0' && label_name[i] != ':'){
      if(isalnum(label_name[i])){
        return FALSE;
      } else{
        i++;
      }
    }
  }
  /*add if the label not equal to :
  mcro 
  instruction
  directive 
  register*/
}
struct Label* create_label(char label_name, int label_address, label_type label_character){
  struct Label* new_label = (struct Label*)malloc(sizeof(struct Label));
  strcpy(new_label -> label_name, label_name);
  new_label -> label_address = label_address;
  new_label -> label_character = label_character;
  new_label -> next = NULL;
  return new_label;
}
struct Label* insert_label_to_table(struct Label* label_list, char label_name, int label_address, label_type label_character){
  if()
  struct Label* new_label = create_label(label_name, label_address, label_character);
  if(label_list == NULL){
    return new_label;
  }
  if
  struct label* head = label_list;
  while(head -> next != NULL){
    head = head -> next;
  }
  head -> next = new_label;
  return label_list;
}

boolean check_label_exist(struct Label* label_list, char label_name){
  if(label_list == NULL){
    return FALSE;
  }
  struct label* head = label_list;
  while(head -> next != NULL){
    if (strcmp(head -> label_name, label_name)){
      return TRUE;
    }
  }
  return FALSE;

}
