
#define __POSIX_C_SOURCE >= 200809L
#include <assert.h>
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

void add_node(char *strPtr); // Adds new node to list on TOP of list
void remove_list(void);      // frees all data from listTop linked list. Run ONCE prior main return
void removeLast_node(void);  // Removes the node at the END of the list (ie oldest)
void print_node(node *node); // Prints ONLY the node that is ptr'd to
void print_list(void);       // Prints ALL in list (Top -> bottom, Recent->old)

int main() {
  listTop = NULL;
  char *strPtr = {"hello"};
  // TODO:
  // Infinite loop of user intput
  //  each node takes one string value -> use getline() to pull inputs,
  //  then load into 'each node' -> needs to loop actively :)
  //
  add_node(strPtr);
  add_node(strPtr);
  add_node(strPtr);
  print_list();
  printf("\n");

  removeLast_node();
  print_list();
  printf("\n");

  remove_list();
  print_list();

  return 0;
}

// Add a node to 'top' of list, change listTop to point to new node,
// previous listTop/'head' of list becomes new node's tail ptr,
// old node's head ALSO changes to new node.
void add_node(char *str) {
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
    listTop->head = node_new; // set old node's head ptr to be our new node
    listTop = node_new;       // set new top of list to be new node
  }
}

void remove_list() {
  while (listTop != NULL) {
    removeLast_node();
  }
  if (listTop->tail != NULL && listTop->head != NULL) {
    perror("remove_list error");
    exit(-1);
  }
}
// traverse list and remove last node
void removeLast_node() {
  node *nodePtr = listTop;

  while (nodePtr->tail != NULL) {
    nodePtr = nodePtr->tail;
  }
  if (nodePtr == listTop) {
    printf("HERE");
    free(nodePtr);
    nodePtr = NULL;
    listTop = NULL;
  }
  nodePtr = nodePtr->head;
  free(nodePtr->tail);
  nodePtr->tail = NULL;

  if (nodePtr->tail != NULL) {
    perror("Error in removeLast_node");
    exit(-1);
  }
}

// Print the string held by an individual node.
void print_node(node *node) {
  if (node->str == NULL || node == NULL) {
    perror("print_node Error: Tried to print an empty string!");
    exit(-1);
  } else {
    printf(">%s\n", node->str);
  }
}

// Print All nodes saved in list, access via listTop
void print_list() {
  node *nodeTemp = listTop;
  if (listTop == NULL) {
    printf("print_list: No history to print");
    return; // Exit immediately if no list to print
  }
  while (nodeTemp != NULL && listTop != NULL) {
    if (nodeTemp == NULL && listTop != NULL) {
      return;
    }
    print_node(nodeTemp);
    nodeTemp = nodeTemp->tail;
  }
}
