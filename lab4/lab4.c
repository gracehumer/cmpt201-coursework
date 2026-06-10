
#define _DEFAULT_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Lab 4 - main file
 *
 * Grace Humer, CMPT201 Sumer 2026
 */

// DEFINE PROTOTYPES HERE

// DEFINE STRUCTS/ETC
typedef struct header { // size of WHOLE header is 16 bytes (8 for size, 8 for ptr)
  uint64_t size;
  struct header *next;
} header_mem;

#define HEADER_SIZE sizeof(struct header);

// MAIN PROGRAM
int main() {
  const intptr_t heapIncrease = 256;                    // 256 bytes
  const uint64_t block_size = 128;                      // each block size total
  const uint64_t header_size = sizeof(struct header);   // header size
  const uint64_t actual_mem = block_size - header_size; // actual size of free memory

  printf("Header size in bytes: %lu\n", sizeof(struct header));

  void *program_break = sbrk(0);
  printf("initial Program Break: %p\n", program_break);
  // Assume we are given our additional bytes if returns previous address. This address is START of
  // new memory block
  void *new_program_break = sbrk(heapIncrease);
  printf("Memory added at address: %p\n", new_program_break);

  struct header *block_one = (struct header *)new_program_break;
  block_one->size = block_size;
  block_one->next = NULL;

  // print header
  // set memory using memset()
  // reprint to verify no corruption

  printf("HEADER: Size = %lu, Next = %p\n", block_one->size, block_one->next);

  void *mem_block_one = new_program_break + header_size;
  void *return_block_one = memset(mem_block_one, 0, actual_mem);
  printf("%p\n%p", mem_block_one, return_block_one);
  printf("HEADer: Size = %lu, Next = %p\n", block_one->size, block_one->next);
  struct header *block_two = (struct header *)(new_program_break + block_size);
  block_two->size = block_size;
  block_two->next = new_program_break;

  return 0;
}

// FUNCTION IMPLEMENTATIONS HERE
