start: mov r1, r2
mcro my_macro a
label_inside_macro: add r3, r4

bne label_inside_macro
mcroend e

my_macro

mcro invalid_macro
should not fail
mcroend

invalid_macro
my_macro

hello world noa
this is a simple project
bla bla
hello world

MAIN:  add   r3,LIST
LOOP:  prn   #48
       lea   STR,r6
       inc   r6
       mov   r3,k