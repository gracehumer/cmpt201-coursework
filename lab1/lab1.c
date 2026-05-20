
#include <stdio.h>

// Program in C for Lab 1: Command line text input to terminal output.

/*  CMPT201 - Summer 2026, May 19
    Grace Humer, 301351393
    ghumer@sfu.ca
    Last edited: May 19 */

/* Write a program that recieves a full line of user (keyboard) input
tokenizes it with delimiter " " (space)
Prints out each token one at a time on a new line
Use getline() for user input and strtok_r() for tokenization
Then make it loop to keep accepting new input

Example output:
Please enter some text: Tomorrow is Friday.
Tokens:
 Tomorrow
 is
 Friday.
Please enter some text: Hello! World!
Tokens:
 Hello!
 World!

And repeat */
