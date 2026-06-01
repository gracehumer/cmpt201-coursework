
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

  while (CONT) {
    puts("Enter programs to run.");

    if (getline(&str, &str_len, stdin) == -1) { // Error Handling if weird input

      perror("getline() failure");
      exit(EXIT_FAILURE);

    } else if (*str == '\n') {

      printf("DONE");
      CONT = 0; // Exit infinite while loop

    } else if (1) {

      printf(">%s", str);
      pid_t parent = getpid();
      pid_t child = fork();

      if (parent == getpid()) {
        printf("REACHED");
        int *status = NULL;
        waitpid(child > 0, status, WEXITED);

      } else if (child == -1) {
        perror("fork failure");
        exit(EXIT_FAILURE);
      }
      char *ret = NULL;
      char *hold_temp = NULL;
      char *hold_path = NULL;
      ret = strtok_r(str, "/", &ret);
      printf("%s, %s, %s, %s", str, ret, hold_temp, hold_path);

      while (ret != NULL) {
        printf("HERE");
        ret = strtok_r(NULL, "/", &ret);
        hold_path = strcat(hold_path, hold_temp);
        hold_temp = ret;
      }
      printf("%s, %s", hold_path, hold_temp);
      execl(hold_path, hold_temp);
    }
    free(str);
    str = NULL;
  }
  return 0;
}
