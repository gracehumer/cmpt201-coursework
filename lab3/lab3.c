
#define __POSIX_C_SOURCE >= 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lab 3 - main file, lab3.c
 * Read, store, and print user input (up to 5 lines)
 * Grace Humer, CMPT201 - Summer 2026
 * Last Modified: June 1st, 2026
 */
// MAY HAVE TO CHANGE TO TWO SIMPLE ARRAYS OF LEN 5 each
// 5INCE 5 PTRS AND INT LEN -> STABLE/CONSTANT SIZING
struct user_history { // struct of 5 pointers and their lengths, ordered by input
  char *str_1;        // most recent input string
  size_t len1;        // string length
  char *str_2;
  size_t len2;
  char *str_3;
  size_t len3;
  char *str_4;
  size_t len4;
  char *str_5; // least recent input
  size_t len5; // string length
};

void init_user_history(struct user_history history);
void increment_history(struct user_history history, char *str);

int main() {
  struct user_history userHistory;
  init_user_history(userHistory);
  getline(userHistory.str_1, userHistory.len1, stdin);
  // getline SHOULD work, unsure why its not :(
  printf("%s", userHistory.str_1);
  return 0;
}

// Clears struct of any lingering data from allocation
void init_user_history(struct user_history history) {
  while (history.str_5 != NULL && history.len5 != 0) {
    increment_history(history, NULL);
  }
}

// shift all strings by one, dropping old string 5
void increment_history(struct user_history history, char *str) {
  history.str_5 = history.str_4;
  history.len5 = history.len4;
  history.str_4 = history.str_3;
  history.len4 = history.len3;
  history.str_3 = history.str_2;
  history.len3 = history.len2;
  history.str_2 = history.str_1;
  history.len2 = history.len1;
  // fill str_1 with new string and assc. length
  history.str_1 = str;

  if (str == NULL) {
    history.len1 = 0;
  } else {
    history.len1 = strlen(str);
  }
}
