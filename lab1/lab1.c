
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Program in C for Lab 1: Command line text input to terminal output.

/*  CMPT201 - Summer 2026, May 19
 *  Grace Humer, 301351393
 *  ghumer@sfu.ca Last edited: May 23 */

/*  LAB INSTRUCTIONS:
 *  Write a program that recieves a full line of user (keyboard) input
 *  tokenizes it with delimiter " " (space)
 *  Prints out each token one at a time on a new line
 *  Use getline() for user input and strtok_r() for tokenization
 *  Then make it loop to keep accepting new input
 *
 *  Example output:
 *  Please enter some text: Tomorrow is Friday.
 *  Tokens:
 *  Tomorrow
 *  is
 *  Friday.
 *  Please enter some text: Hello! World!
 *  Tokens:
 *  Hello!
 *  World!
 *
 *  And repeat */

int main() {
  int CONT = 1;

  char *str = NULL;
  size_t str_len = 0;
  ssize_t str_mk;

  while (CONT != 0) {
    puts("Please enter some text: ");
    str_mk = getline(&str, &str_len, stdin);

    if (str_mk == -1) {         // If no string is input, getline() will return -1
      perror("getline failed"); // RESULT: Throw error and exit program
      exit(EXIT_FAILURE);
    } else if (*str == '\n') {       // Elif string is '\n' (ie enter key only)
      printf("thanks for playing!"); // RESULT: Thank and exit program
      exit(0);
    } else { // Else tokenize input as requested =^.^=
      printf("Tokens:");

      char *saveptr;
      char *ret = strtok_r(str, " ", &saveptr); // strtok_r(), r is for recursion (probably)

      while (ret != NULL) {
        printf("\n\t%s", ret);
        ret = strtok_r(NULL, " ", &saveptr); // Second, third, etc. calls of strtok_r() are
                                             // DIFFERENT from the first.
                                             // (first initalize,then repeat until EOF)
      }
    }
  }

  free(str); // Manual for a function mentioned needing to free str at end
  str = NULL;

  return 0;
}
