#include "assembler.h"
#define BITS_NUMBER 6
int main(int argc, char *argv[]){ 
  char hex ='0';
  char *binary, *binary_bits_word;
  char *word_hex = malloc(6);
  printf("the number is %s \n",decimal_to_binary(-18,16));
  binary = "0101";
  hex = convert_binary_to_hex(binary);
  printf("the number is %c \n",hex);
  binary_bits_word = "000000110011110000010100";
  word_hex = convert_word_binary_to_hex(binary_bits_word);
  printf("the number is %s \n",word_hex);
  free(word_hex);
  
  return 0;
}

/*This function convert decimal number to binary number and return binary number
  input:
      decimal_number- The number we want to convert in base 2.
      bits_number- number bits of the binary number
    output: 
      binary_number- The number after convertion to base 2
*/
char *decimal_to_binary(int decimal_number, int bits_number){
    int i = 0;
    char *binary_number = malloc(bits_number);
    int mask = 1 << (bits_number-1);
    while(mask){
      binary_number[i] = (mask & decimal_number) ? '1' : '0';
      mask >>= 1;
      i++;
    }
    return binary_number;
}

/*This function convert binary number to hexadecimal number and return hexadecimal number as char
  input:
      binary_number- The number we want to convert in base 16, the variable is array lengh 4.
    output: 
      hex_number- The number after convertion to base 16, the variable is char type
*/
char convert_binary_to_hex(char *binary_number){
  int i = 0;
  int convert_number = 0;
  char hex_number = '0';
  for (i = 0; i < 4; i++){
    convert_number += (binary_number[i] - '0' )* (pow(2,3-i));
  }
  if (convert_number > 9){
      switch(convert_number){
        case 10:
          hex_number = 'a';
          break;
        case 11:
          hex_number = 'b';
          break;
        case 12:
          hex_number = 'c';
          break;
        case 13:
          hex_number = 'd';
          break;
        case 14:
          hex_number = 'e';
          break;
        case 15:
          hex_number = 'f';
          break;
      }
  } else{
    hex_number = convert_number + '0';
  }
  return hex_number;
}

/*This function convert 'word' binary number with 23 bits to hexadecimal number as a string
  input:
      binary_number- The number we want to convert in base 16, the variable is array lengh 24, .
    output: 
      hex_number- The number after convertion to base 16, the variable is *char type
*/
char *convert_word_binary_to_hex(char *binary_number){
  char *hex_number = malloc(4);
  char part_binary_number[4] = {0};
  int i , j;
  i = j = 0;
  for(i = 0; i < 23; i += 4){ /*every loop we take 4 bits and convert them to one hexadecimal number*/
    memcpy(part_binary_number, binary_number + i, sizeof(char) * 4); /*copy part of the binary number (4 lengh) */
    hex_number[j] = convert_binary_to_hex(part_binary_number); /*call to the function that convert binary to hexadecimal*/
    memset(part_binary_number, 0, 4*sizeof(part_binary_number[0])); /*initialize the array by memset function*/
    j++;
  }
  return hex_number;
}


