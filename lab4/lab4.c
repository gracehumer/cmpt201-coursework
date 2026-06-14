
#define _DEFAULT_SOURCE
#define __POSIX_C_SOURCE 200809L

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Lab 4 - main file
 *
 * Grace Humer, CMPT201 Summer 2026
 */

typedef struct header { // size of WHOLE header is 16 bytes (8 for size, 8 for ptr)
  uint64_t size;
  struct header *next;
} header_mem;

#define HEADER_SIZE sizeof(struct header);

struct header *fill_header(struct header *header, uint64_t block_size, struct header *block_next);
struct header *fill_data(struct header *header, int fill, size_t mem_size);
struct header *fill_block(struct header *header, uint64_t block_size, struct header *block_next,
                          int fill, size_t mem_size);
void print_header(struct header *header);
void print_data(struct header *header);
void print_block(struct header *header);
void print_out(char *format, void *data, size_t data_size);

// MAIN PROGRAM
int main() {
  const intptr_t heapIncrease = 256;                    // 256 bytes
  const uint64_t block_size = heapIncrease / 2;         // each block size total
  const uint64_t header_size = sizeof(struct header);   // header size
  const uint64_t actual_mem = block_size - header_size; // actual size of free memory

  // struct header *b1_data;
  // struct header *b2_data;

  void *program_break = sbrk(0);
  void *new_program_break = sbrk(heapIncrease);
  assert(program_break == new_program_break);

  // print_out("program break (top of heap): %p\n", &program_break, sizeof(program_break));

  // struct header *block_one = fill_header(program_break, block_size, NULL);
  // struct header *block_two = fill_header(program_break + block_size, block_size, program_break);

  // print_header(block_one);
  // print_header(block_two);

  // b2_data = fill_data(block_two, 11, actual_mem);
  // b2_data = fill_data(block_two, 11, actual_mem);

  // print_header(block_one);
  // print_header(block_two);

  // print_data(b1_data);
  // print_data(b2_data);

  // print_block(block_one);
  // print_block(block_two);

  struct header *block_one =
      fill_block((struct header *)new_program_break, block_size, NULL, 0, actual_mem);
  struct header *block_two = fill_block((struct header *)(new_program_break + block_size),
                                        block_size, new_program_break, 1, actual_mem);

  print_block(block_one);
  print_block(block_two);

  return 0;
}

// FUNCTION IMPLEMENTATIONS HERE

// header is ptr to entire memory block, size is the size of the memory block (header + actual free)
// next is the ptr to the 'next' block of memory - NULL if bottom.
struct header *fill_header(struct header *header, uint64_t block_size, struct header *block_next) {
  header->size = block_size;
  header->next = block_next;
  return header;
}

// Fills data block of size mem_size with value of fill (0 or 1)
struct header *fill_data(struct header *header, int fill, size_t mem_size) {
  void *data = (void *)header + sizeof(struct header);
  memset(data, fill, mem_size);
  return header;
}
// Fills entire memory block.
struct header *fill_block(struct header *header, uint64_t block_size, struct header *block_next,
                          int fill, size_t mem_size) {
  header = fill_header(header, block_size, block_next);
  header = fill_data(header, fill, mem_size);
  return header;
}

// Prints header values: size and ptr to next free memory, NULL if bottom
void print_header(struct header *header) {
  char *str = "\nHEADER: ";
  write(1, str, strlen(str));
  print_out("\tcurrent address: %p\n", &header, sizeof(struct header));
  print_out("\tsize: \t%d\n", &(header->size), sizeof(uint64_t));
  print_out("\tnext: \t%p\n", &(header->next), sizeof(struct header *));
}

// Prints data associated with a given header. should already be intitalized to be 0 or 1.
void print_data(struct header *header) {
  char *str = "\nDATA: ";
  write(1, str, strlen(str));
  void *data = (void *)header + sizeof(struct header);
  uint64_t memory = (header->size) - sizeof(struct header);
  for (uint64_t i = 0; i < memory - 4; i++) {
    print_out("%x\n", data, 1); // Could not get the final result to print correctly :( unsure which
                                // data type to cast to since I assume we want a direct
                                // representation of the value, and not a if/else to print the
                                // correct value :)
  }
}

// Prints the block of memory (header + data)
void print_block(struct header *header) {
  print_header(header);
  print_data(header);
}

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUFSIZ];
  ssize_t len = snprintf(buf, BUFSIZ, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);
  if (len < 0) {
    perror("snprintf");
  }
  write(1, buf, len);
}
