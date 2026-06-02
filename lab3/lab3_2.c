
#define __POSIX_C_SOURCE >= 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Lab 3 - main file, lab3.c
 * Read, store, and print user input (up to 5 lines)
 * Grace Humer, CMPT201 - Summer 2026
 * Last Modified: June 2nd, 2026
 */

typedef struct node {
  char *str;
  struct node *head;
  struct node *tail;
} node; // six bytes for struct -> largest bytes define 'set size' (ours is short -> 2x)

node *listTop;

void addTop_node(char *strPtr); // Adds new node to list on TOP of list
void remove_node(node *node);   // Removes single node from list, and will clear listTop if needed
void removeLast_node();         // Removes the node at the END of the list (ie oldest)
void removeEnd_node();          // Checks if last node in list, clears listTop if so
void print_node(node *node);    // Prints ONLY the node that is ptr'd to
void print_list();              // Prints ALL in list (Top -> bottom, Recent->old)

int main() {
  listTop = NULL;
  char *strPtr = {"hello"};
  // TODO:
  // Infinite loop of user intput
  //  each node takes one string value -> use getline() to pull inputs,
  //  then load into 'each node' -> needs to loop actively :)
  //  print whole list
  //
  addTop_node(strPtr);
  print_list();
  return 0;
}

void addTop_node(char *str) {
  node *node_new = malloc(sizeof(node));
  if (node_new == NULL) {
    perror("malloc error");
    // free(input)
    exit(-1);
  } else if (listTop == NULL) {
    node_new->str = str;
    node_new->head = NULL;
    node_new->tail = NULL;
    listTop = node_new;
  } else {
    node_new->str = str;      // save string ptr
    node_new->head = NULL;    // clear head; top of list
    node_new->tail = listTop; // set tail to be old top of list
    listTop = node_new;       // set new top of list to be new node
  }
}

void remove_node(node *node) {
  if (node->tail == NULL && node->head == NULL) {
    removeEnd_node();
  } else if (node->tail == NULL) {
    removeLast_node();
  } else {
    perror("Error in remove_node");
    exit(-1);
  }
}

// traverse list and remove last node
void removeLast_node() {
  node *nodePtr = listTop;
  while (nodePtr->tail != NULL) {
    nodePtr = nodePtr->tail;
  }
  nodePtr = nodePtr->head;
  free(nodePtr->tail);
  nodePtr->tail = NULL;
  if (nodePtr->tail != NULL) {
    perror("Error in removeLast_node");
    exit(-1);
  }
}

// when single node in list, reset list to empty ('end list')
void removeEnd_node() {
  if (listTop->tail == NULL && listTop->head == NULL) {
    free(listTop);
    listTop = NULL;
  } else {
    perror("Error in removeEnd_node()");
    exit(-1);
  }
}

void print_node(node *node) { printf("%s :: ", node->str); }

void print_list() {
  node *nodeTemp = listTop;
  printf("REACHED");
  while (nodeTemp->tail != NULL) {
    print_node(nodeTemp);
    nodeTemp = nodeTemp->tail;
  }
  if (nodeTemp == listTop && listTop != NULL) {
    print_node(nodeTemp);
  }
}
