
#define __POSIX_C_SOURCE 200809L
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HISTORY_LENGTH 5

/* Lab 3 - main file, lab3.c
 * Read, store, and print user input (up to 5 lines)
 * Grace Humer, CMPT201 - Summer 2026
 * Last Modified: June 7th, 2026
 */

typedef struct node {
  char *str;
  struct node *head;
  struct node *tail;
} node; // six bytes for struct -> largest bytes define 'set size' (ours is short -> 2x)

node *listTop;

void add_node(char *strPtr); // Adds new node to list
struct node *init_node(struct node *node, char *str, struct node *head, struct node *tail);
// takes pointer to node, assigns str, head/tail nodes to node. returns ptr to node.
void remove_list(void);      // frees all data from listTop linked list. Run ONCE prior main return
void removeLast_node(void);  // Removes the node at the END of the list (ie oldest)
void print_node(node *node); // Prints ONLY the node that is ptr'd to
void print_list(void);       // Prints ALL in list (Top -> bottom, Recent->old)
int list_len(void);          // Counts nodes in list, using listTop

int main() {
  // test cases to add/remove nodes from the linked list
  // All lines (40-63) can be un-commented and do run :)
  /*
  listTop = NULL;
  char *strPtr = {"hello"};
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
  printf("\n");

  for (int i = 0; i < 7; i++) {
    add_node(strPtr);
    printf("%d :", i);
  }
  print_list();
  printf("\n");

  remove_list();
  print_list();
*/
  listTop = NULL;
  int CONT = 1;
  char *user_str = NULL;
  size_t user_str_len = 0;
  ssize_t str_in;
  // Infinite loop, prompting input of any string
  while (CONT == 1) {
    puts("Enter input: ");

    // I have an error I cannot explain or understand :(
    // states the 'call to undeclared function 'getline'; ISO C99..."
    // However I have declared the posix source just as we did in a previous lab and it doesn't work
    //'#define __POSIX_C_SOURCE 200809L' specifically :(
    str_in = getline(&user_str, &user_str_len, stdin);
    assert(str_in != -1);

    // Unsure if this is the correct method of comparison, getline was not working :(
    // and am unable to test it fully
    if (strcmp(user_str, "print") == 0 || strcmp(user_str, "PRINT") == 0 ||
        strcmp(user_str, "Print") == 0) {
      add_node(user_str); // add node w 'str' value
      print_list();       // print new list of history

    } else if (strcmp(user_str, "exit") == 0 || strcmp(user_str, "EXIT") == 0 ||
               strcmp(user_str, "Exit") == 0) {
      CONT = 0; // added an exit condition to allow clean exit (ie free all memory)
    } else {
      add_node(user_str); // if str is not either print or exit, add string as str in node
    }
  }
  remove_list();
  return 0;
}

// Add a node to 'top' of list, change listTop to point to new node,
// previous listTop/'head' of list becomes new node's tail ptr,
// old node's head ALSO changes to new node.
void add_node(char *str) {
  node *node_new = malloc(sizeof(node));
  if (node_new == NULL) {
    perror("malloc error");
    exit(-1);
  } else if (listTop == NULL) {
    listTop = init_node(node_new, str, NULL, NULL);
  } else if (list_len() >= HISTORY_LENGTH) { // Trim list if history is at/longer than
                                             // HISTORY_LENGTH
    while (list_len() > HISTORY_LENGTH) {
      removeLast_node();
    }
    assert(list_len() == HISTORY_LENGTH);
    listTop->head = init_node(node_new, str, NULL, listTop);
    listTop = node_new; // set new top of list to be new node
    removeLast_node();
    assert(list_len() == HISTORY_LENGTH);

  } else if (list_len() < HISTORY_LENGTH) {
    listTop->head = init_node(node_new, str, NULL, listTop);
    listTop = node_new;
    assert(list_len() <= HISTORY_LENGTH);
  }
}

// Take ptr to node, fills node's str, head and tail. returns ptr to node. node MUST be allocated
// prior to call. str, head, tail may be null.
// returns inital ptr to node.
struct node *init_node(struct node *node, char *str, struct node *head, struct node *tail) {
  node->str = str;
  node->head = head;
  node->tail = tail;
  return node;
}

void remove_list() {
  assert(listTop->head == NULL);
  while (listTop->tail != NULL) {
    removeLast_node();
  }
  if (listTop->tail != NULL && listTop->head != NULL) {
    perror("remove_list error");
    exit(-1);
  } else {
    assert(listTop->tail == NULL);
    assert(listTop != NULL);
    free(listTop);
    listTop = NULL;
  }
}

// traverse list and remove last node, assumed ALWAYS to have more than one node
void removeLast_node() {
  assert(listTop != NULL);
  node *nodePtr = listTop;
  while (nodePtr->tail != NULL) {
    nodePtr = nodePtr->tail;
  }
  nodePtr = nodePtr->head;
  free(nodePtr->tail);
  nodePtr->tail = NULL;

  if (nodePtr->tail != NULL) {
    free(nodePtr);
    perror("Error in removeLast_node");
    exit(-1);
  }
}

// Print the string held by an individual node.
void print_node(node *node) {
  assert(node != NULL);
  if (node->str == NULL) {
    perror("print_node Error: Tried to print an empty string!");
    exit(-1);
  } else {
    printf(">%s\n", node->str);
  }
}

// Print All nodes saved in list, access via listTop
void print_list() {
  if (listTop == NULL && list_len() == 0) {
    printf("print_list: No history to print\n");
    return; // Exit immediately if no list to print
  }
  node *nodeTemp = listTop;
  while (nodeTemp != NULL && listTop != NULL) {
    if (nodeTemp == NULL && listTop != NULL) {
      return;
    }
    print_node(nodeTemp);
    nodeTemp = nodeTemp->tail;
  }
}

int list_len() {
  int i = 0;
  node *nodeTemp = listTop;
  while (nodeTemp != NULL) {
    i += 1;
    nodeTemp = nodeTemp->tail;
  }
  return i;
}
