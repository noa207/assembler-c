#include "assembler.h"

int main(int argc, char *argv[]) {
    check_file(argc, argv);
    create_file("hello","as");
    append_line_to_file("hello world\n", "hello.as");
    append_line_to_file("mcro a_fj\n", "hello.as");
    append_line_to_file("label: odfjepi\n", "hello.as");
    append_line_to_file("mcroend\n", "hello.as");
    append_line_to_file("mcro a_fj\n", "hello.as");
    /*append_line_to_file("mcro \n", "hello.as");
    append_line_to_file("12344\n", "hello.as");
    append_line_to_file("mcroend\n", "hello.as");
    append_line_to_file("mcro \n", "hello.as");*/

    char *inputfile = "hello.as";
    char *outputfile = "hello.am";


    store_mcros(inputfile);
    create_file_am(inputfile, outputfile);

    release_memory();

    printf("Processing complete. Output written to %s\n", outputfile);
    return 0;
}
