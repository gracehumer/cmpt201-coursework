
/* Lab 6 - lab6.c main file
 * Composed of both examples from Lab 6, example_1.c and example_2.c, lab6.c does not run.
 *
 * Apologies if there are any errors in this file, as I had to transcribe the files by hand as I was
 * unable to get copy/paste to work between the different files :(
 *
 * Grace Humer, CMPT201 - Summer 2026
 */

/* EXAMPLE 1: example_1.c */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr)                                                                               \
  {                                                                                                \
    \ 
  if (!(expr)) {                                                                                   \
      fprintf(strderr, "Assertion failed: %s\n", #expr);                                           \
      exit(1);                                                                                     \
    }                                                                                              \
  }

#define TEST(expr)                                                                                 \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Test failed: %s\n", #expr);                                                 \
      exit(1);                                                                                     \
    } else {                                                                                       \
      printf("Test passed: %s\n", #expr);                                                          \
    }                                                                                              \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

node_t *head = NULL;

void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
  } else {
    node_t *curr = head;
    node_t *prev = NULL;

    bool inserted = false;

    if (data < head->data) {
      new_node->next = head;
      head = new_node;
      inserted = true;
    }

    while (!inserted) {
      if (curr == NULL || data < curr->data) {
        prev->next = new_node;
        new_node->next = curr;
        inserted = true;
      }
      if (curr != NULL) {
        prev = curr;
        curr = curr->next;
      }
    }
  }
}

int index_of(uint64_t data) {
  node_t *curr = head;
  int index = 0;

  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }

    curr = curr->next;
    index++;
  }
  return -1;
}

int main() {
  insert_sorted(1);
  insert_sorted(2);
  insert_sorted(5);
  insert_sorted(3);

  TEST(index_of(3) == 2);

  insert_sorted(0);
  insert_sorted(4);

  TEST(index_of(4) == 4);

  return 0;
}

/* EXAMPLE 2: example_2.c */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ASSERT(expr)                                                                               \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Assertion failed: %s\n", #expr);                                            \
      fprintf(stderr, "File: %s,\tLine:%d\n", __FILE__, __LINE__);                                 \
      exit(1);                                                                                     \
    }                                                                                              \
  }

#define TEST(expr)                                                                                 \
  {                                                                                                \
    if (!(expr)) {                                                                                 \
      fprintf(stderr, "Test failed: %s\n", #expr);                                                 \
      exit(1);                                                                                     \
    }                                                                                              \
  }

typedef struct node {
  uint64_t data;
  struct node *next;
} node_t;

typedef struct info {
  uint64_t sum;
} info_t;

node_t *head;
info_t info = {0};

void insert_sorted(uint64_t data) {
  node_t *new_node = malloc(sizeof(node_t));
  new_node->data = data;
  new_node->next = NULL;

  if (head == NULL) {
    head = new_node;
  } else if (data < head->data) {
    new_node->next = head;
    head = new_node;
  } else {
    node_t *curr = head;
    node_t *prev = NULL;

    while (curr != NULL) {
      if (data < curr->data) {
        break;
      }
      prev = curr;
      curr = curr->next;
    }

    prev->next = new_node;
    if (curr != NULL) {
      new_node->next = curr;
    }
  }
  info.sum += data;
}

int index_of(uint64_t data) {
  node_t *curr = head;
  int index = 0;

  while (curr != NULL) {
    if (curr->data == data) {
      return index;
    }

    curr = curr->next;
    index++;
  }

  return -1;
}

// Return sum of all elements in list
uint64_t sum_elements() {
  node_t *ptr = head;
  uint64_t value = 0;

  if (head == NULL) {
    return 0;
  }

  while (ptr != NULL) {
    value = value + ptr->data;
    ptr = ptr->next;
  }
  return value;
}

int main() {
  insert_sorted(1);
  ASSERT(sum_elements() == 1);
  insert_sorted(3);
  ASSERT(sum_elements() == 1 + 3);
  insert_sorted(5);
  ASSERT(sum_elements() == 1 + 3 + 5);
  insert_sorted(2);
  ASSERT(sum_elements() == 1 + 2 + 3 + 5);

  TEST(info.sum == 1 + 3 + 5 + 2);

  TEST(index_of(1) == 0);
  TEST(index_of(2) == 1);
  TEST(index_of(3) == 2);
  TEST(index_of(5) == 3);

  ASSERT(sum_elements() == info.sum);

  printf("All tests passed! Good job! :) ");

  return 0;
}
