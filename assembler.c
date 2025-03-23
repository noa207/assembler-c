#include "assembler.h"

/*int main(int argc, char *argv[]) {
    int number = pre_process(argv[1]);
    if( number == 0){
        printf("ok");
    } else{
        printf("basa");
    }
    
    printf("Processing complete. Output written to \n");
    return 0;
}*/

int main(int argc, char *argv[]) {
    /* Check if a filename was provided*/
    int number;
    if (argc < 2) {
        fprintf(stderr, "ERROR: No input file provided.\n");
        /*fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);*/
        return 1;
    }
    number = pre_process(argv[1]);

    /* Print success or failure message */
    if (number == 0) {
        printf("ok\n");
    } else {
        printf("basa\n");
    }

    printf("Processing complete. Output written to %s.am\n", argv[1]);
    return 0;
}


/* Test the function */
/*int main() {
    char input[] = "hello world this is C";
    char **words = split_line(input);

    if (words) {
        for (int i = 0; words[i] != NULL; i++) {
            printf("Word[%d]: %s\n", i, words[i]);
            free(words[i]);  // Free each word
        }
        free(words);  // Free the word array
    }

    return 0;
}*/
