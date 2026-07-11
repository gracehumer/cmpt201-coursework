
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT 100

/*Lab 7 - Map Reduce
 * Grace Humer, CMPT201 Summer 2026*/

typedef struct {
  int line_number;
  int value;
} Input;

typedef struct {
  int line_number;
  int double_value;
} IntermediateInput;

typedef struct {
  int doubled_value;
  int line_numbers[MAX_INPUT];
  int count;
} Output;

void map(Input *input, IntermediateInput *intermediate_input);
void groupByKey(IntermediateInput *input, Output *output, int *result_count);
void reduce(Output *output);

// helper functions
void printInput(Input *input, int input_size);
void printIntermediateInput(IntermediateInput *intInput, int input_size);
void printOutput(Output *output, int result_size);

int main() {
  Input input_data[MAX_INPUT];
  int input_size = 0;
  int value;

  // Read input value until "end" is encountered
  printf("Enter values (one per line). Type 'end' to finish:\n");
  while (input_size < MAX_INPUT) {
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      break;
    }
    if (sscanf(buffer, "%d", &value) == 1) {
      input_data[input_size].line_number = input_size + 1;
      input_data[input_size].value = value;
      input_size++;
    } else if (sscanf(buffer, "end") == 0) {
      break;
    } else {
      printf("Invalid input. Please enter an integer or 'end' to finish.\n");
    }
  }

  // Step 1: Map Phase

  IntermediateInput mapped_results[MAX_INPUT] = {0};
  printInput(input_data, input_size);

  for (int i = 0; i < input_size; i++) {
    map(&input_data[i], &mapped_results[i]);
  }

  // Step 2: Grouping Phase

  Output output_results[MAX_INPUT] = {0};
  int result_count = 0;
  printIntermediateInput(mapped_results, input_size);

  for (int i = 0; i < input_size; i++) {
    groupByKey(&mapped_results[i], output_results, &result_count);
  }

  // Step 3: Reduce phase
  for (int i = 0; i < result_count; i++) {
    if (output_results[i].count > 0) {
      reduce(&output_results[i]);
    }
  }

  return 0;
}

// Double the value of the input
void map(Input *input, IntermediateInput *intermediate_input) {
  intermediate_input->double_value = input->value * 2;
  intermediate_input->line_number = input->line_number;
}

// Group entries
// if doubled value exists in output entries, add it to the output's line_numbers list
// if it doesn't exist, add a new entry to the output
void groupByKey(IntermediateInput *input, Output *output, int *result_count) {
  for (int i = 0; i < *result_count; i++) {
    if (input->double_value == output[i].doubled_value) {
      for (int j = 0; j < output[i].count + 1; j++) {
        if (output[i].line_numbers[j] == '\0') {
          output[i].line_numbers[j] = input->line_number;
          output[i].line_numbers[j + 1] = '\0';
          output[i].count++;
          return;
        }
      }
    }
  }
  output[*result_count].doubled_value = input->double_value;
  output[*result_count].line_numbers[0] = input->line_number;
  output[*result_count].count = 1;
  *result_count = *result_count + 1;
  // No matches found. THEREFORE:
  // add new entry to output
  // then increment result count
}

void reduce(Output *output) {
  // Print the doubled number and the line numbers
  printf("%d\t", output->doubled_value);
  for (int j = 0; j < output->count; j++) {
    printf("%d ", output->line_numbers[j]);
  }
  printf("\n");
}

void printInput(Input *input, int input_size) {
  printf("Printing Initial Input:\n");
  for (int i = 0; i < input_size; i++) {
    // print input
    printf("%d\t%d\n", input[i].line_number, input[i].value);
  }
}

void printIntermediateInput(IntermediateInput *intInput, int input_size) {
  printf("Printing Intermediate Input:\n");
  for (int i = 0; i < input_size; i++) {
    // print intermediate input
    printf("%d\t%d\n", intInput[i].line_number, intInput[i].double_value);
  }
}

void printOutput(Output *output, int result_count) {
  printf("Printing Output:\n");
  for (int i = 0; i < result_count; i++) {
    // print output
    printf("%d\t[%d]\t", output[i].doubled_value, output[i].count);
    for (int j = 0; j < output->count; j++) {
      printf("%d ", output[i].line_numbers[j]);
    }
    printf("\n");
  }
  printf("\n");
}
