#include "assembler.h"

/*This function convert decimal number to binary number and return binary number
  input:
      decimal_number- The number we want to convert in base 2.
    output: 
      binary_number- The number after convertion to base 2
*/
unsigned int decimal_to_binary(int decimal_number){
    int i = 0;
    unsigned int binary_number = 0;
    while(decimal_number >= 1){
      binary_number += pow(10,i) * (decimal_number % 2);
      decimal_number = decimal_number / 2;
      i++;
    }
    return binary_number;
}

/*This function count the bits in the binary number
  input:
      binary_number- The number we want to count its bits
    output: 
      counter- The bits number of the binary number
*/
int count_bits(unsigned int binary_number){
  int counter = 0;
  while(binary_number > 0){
    binary_number /= 10;
    counter++;
  }
  return counter;
}

/*unsigned int binary_by_bits(unsigned int binary_number, int bits_number){
  unsigned int mask = 0;  
  mask &= 0x3F;
  printf("Number with 6 bits: %u\n", mask);
  if(count_bits(binary_number) == bits_number){
    return binary_number;
  }else{
    binary_number = (binary_number | mask); 
    printf(" the binary try number is %u\n", binary_number);
  }
  
  return binary_number;

    
}
*/
