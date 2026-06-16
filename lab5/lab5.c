
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Lab 5 - CMPT 201
 *
 * Grace Humer
 */

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

// function prototypes
void initialize_block(struct header *block, uint64_t size, struct header *next, int id);
int find_first_fit(struct header *free_list_ptr, uint64_t size);
int find_best_fit(struct header *free_list_ptr, uint64_t size);
int smallest_size(int a, int b);
int small_min_size(int a, int b, int min);
int find_worst_fit(struct header *free_list_ptr, uint64_t size);
void print_fit(char *str, int id);

int main(void) {
  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  print_fit("First-Fit", first_fit_id);
  print_fit("Best-Fit", best_fit_id);
  print_fit("Worst-Fit", worst_fit_id);

  return 0;
}

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

// Traverse LL of free memory, return ID of FIRST (large enough) free memory block
int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *fit_ptr = free_list_ptr;

  while (fit_ptr->next != NULL) {
    if (fit_ptr->size > size) {
      return fit_ptr->id;
    } else {
      fit_ptr = fit_ptr->next;
    }
  }
  perror("find_first_fit(): NO MEMORY AVAILABLE TO FIT :(");
  return -1;
}

// Traverse LL of free memory, return ID of SMALLEST free memory block
int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO
  // traverse linked list, allocate the SMALLEST free block that can fit
  struct header *fit_ptr = free_list_ptr;
  struct header *small_ptr = NULL;
  int cur_size = 0;

  while (fit_ptr != NULL) {
    if (fit_ptr->size == small_min_size(fit_ptr->size, cur_size, size)) {
      small_ptr = fit_ptr;
      cur_size = fit_ptr->size;
    }
    fit_ptr = fit_ptr->next;
  }
  assert(small_ptr != NULL);
  return small_ptr->id;
}

int smallest_size(int a, int b) {
  if (a >= b) {
    return b;
  } else
    return a;
}

// give smallest size back of a, b, without going less than min
// if BOTH are less than min, return -1
int small_min_size(int a, int b, int min) {
  int hold;
  if (a > min && b > min) {
    hold = smallest_size(a, b);
  } else if (a < min && b < min) {
    hold = -1;
  } else if (a > min) {
    hold = a;
  } else if (b > min) {
    hold = b;
  } else {
    perror("small_min_size(): Edge Case found ");
    exit(-1);
  }
  return hold;
}

// Traverse LL of free memory, return ID of LARGEST free memory block
int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *cur_ptr = free_list_ptr;
  struct header *large_ptr = cur_ptr;
  while (cur_ptr != NULL) {
    if (large_ptr->size < cur_ptr->size) {
      large_ptr = cur_ptr;
    }
    cur_ptr = cur_ptr->next;
  }

  if (large_ptr->size < size) {
    perror("find_worst_fit(): No memory available :(");
    exit(-1);
  }
  return large_ptr->id;
}

void print_fit(char *str, int id) { printf("The ID for %s algorithm is: %d\n", str, id); }

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Part 2: Coalescing Contiguous Free Blocks: PSEUDOCODE:
 *
 *    ->Function to defrag 'touching' pieces of memory
 *    ->given an LL of free memory, returns LL of free memory (defragged)
 * coalesce_memory()
 *      initializeArray()           -> get array of first/last memory locations
 *      while(current_ptr != NULL)    -> Traverse
 *          compareAddresses()        -> using current_ptr to LL of free memory, if any addresses
 * from array are adjacent to the current_ptr, 'reabsorb' them into memory resetCurrentPtrToLL()
 *      while(CurrentPtr!=NULL){
 *          assert(ptrAdjacentToFreeMemory() == NULL)
 *      }
 *
 *    -> if specifc address has any free adjacent memory, combines at that location, appends to top
 * of LL compareAddresses() while (ptrAdjacentToFreeMemory()){    ->checks array to see if any
 * addresses are adjacent, will continue if more than SINGLE adjacent node removeNodeCur() ->which
 * current ptr to node removeNodeOther()       ->find OTHER node/address to remove addNewNode() ->
 * single node made from resetting size/ptrs of node w/respect to removed removed nodes
 *    }
 */
