assembler:assembler.o pre_process.o first_process.o convertions.o general.o files.o label.o
	gss -ansi -Wall -pedantic -g assembler.o pre_process.o first_process.o convertions.o general.o files.o label.o
assembler.o: assembler.c pre_process.h first_pass.h
	gcc -ansi -Wall -pedantic assembler.c -o assembler.o
pre_process.o: pre_process.c pre_process.h
	gcc -ansi -Wall -pedantic pre_process.c -o pre_process.o
first_process.o: first_pass.c first_pass.h
	gcc -ansi -Wall -pedantic first_pass.c -o first_pass.o
convertions.o: convertions.c conventions.h
	gcc -ansi -Wall -pedantic convertions.c -o convertions.o
general.o: general.c general.h
	gcc -ansi -Wall -pedantic general.c -o general.o
files.o: files.c files.h
	gcc -ansi -Wall -pedantic files.c -o files.o
label.o: label.c label.h
	gcc -ansi -Wall -pedantic label.c -o label.o



preprocess:
	gcc -Wall -ansi -pedantic funcfile.c pre_process.c main.c -o pre -lm

clean: 
