#include "assembler.h"

int main(int argc, char *argv[]) {
    int number = pre_process(argv[1]);
    if( number == 0){
        printf("ok");
    } else{
        printf("basa");
    }
    
    printf("Processing complete. Output written to \n");
    return 0;
}
