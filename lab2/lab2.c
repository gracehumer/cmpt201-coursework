#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/* LAB 2
 * Program design with fork(), exec(), waitpid()
 * Grace Humer CMPT201 - Summer 2026
 * 301351393, Last Edited: May 27, 2026
 */

int main() {
  int CONT = 1;
  char *str = NULL;
  size_t str_len = 0;
  ssize_t str_count;

  while (CONT) {
    puts("Enter programs to run.");
    str_count = getline(&str, &str_len, stdin);
    if (str_count == -1) { // Error Handling if weird input
      perror("getline() failure");
      exit(EXIT_FAILURE);
    } else if (*str == '\n') {
      printf("DONE");
      CONT = 0; // Exit infinite while loop
    } else {
      printf(">%s", str);
      pid_t parent = getpid();
      pid_t child = fork();
      if (parent == getpid()) {
        int *status = NULL;
        waitpid(child > 0, status, WEXITED);
      } else if (child == getpid()) {
        if (execl(str, str) == -1) { // NEED TO TOKENIZE TO WORK, ISSUES WITH \n
          perror("exec() failure");  // execl -> pass name of application to run as FIRST arg
          exit(EXIT_FAILURE);        // fork() and interactions with waitpid()
        }
      }
    }
    free(str);
    str = NULL;
  }
  return 0;
}
