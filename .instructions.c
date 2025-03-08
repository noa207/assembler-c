struct instruction{
  int opcode;
  int funct;
  char []instruction_name;
  int [] adress_source;
  int []adress_destination; 
};

struct mcro{
  char *mcro_name;
  char *mcro_lines;
};

struct label{
  char *label;
  int address;
}
struct instruction *table_instruction[] = {
  {0, NULL, "mov", [0,1,3], [1,3]},
  {1, NULL, "cmp",[0,1,3], [0,1,3]},
  {2, 1, "add", [0,1,3], [1,3]},
  {2, 2, "sub", [0,1,3], [1,3]},
  {4, NULL, "lea", [1], [1,3]},
  {5, 1, "clr", NULL, [1,3]},
  {5, 2, "not", NULL, [1,3]},
  {5, 3, "inc", NULL, [1,3]},
  {5, 4, "dec", NULL, [1,3]},
  {9, 1, "jmp", NULL, [1,2]},
  {9, 2, "bne", NULL, [1,2]},
  {9, 3, "jsr", NULL, [1,2]},
  {12, NULL, "red", NULL, [1,3]},
  {13, NULL, "prn", NULL, [0,1,3]},
  {14, NULL, "rts", NULL, NULL},
  {15, NULL, "stop", NULL, NULL}
};

