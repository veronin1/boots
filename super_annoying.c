#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool argument_check(int argc, char *argv[]);
void rle_compress(FILE *fp, int input_length, char *output);
int get_file_length(FILE *file);

int main(int argc, char *argv[]) {
  if (!argument_check(argc, argv)) {
    return 1;
  }

  FILE *file = fopen(argv[3], "rb");

  int length = get_file_length(file);

  if (strcmp(argv[1], "-c") == 0) {
    rle_compress(file, length, argv[4]);
  }

  fclose(file);
  return 0;
}

bool argument_check(int argc, char *argv[]) {
  if (argc != 5) {
    printf("Usage: ./boots (-c|-d) (-rle|-huff) <input_file> <output_file>");
    return false;
  }

  if (strcmp(argv[1], "-c") != 0 && strcmp(argv[1], "-d") != 0) {
    printf("First argument must be -c or -d.\n");
    return false;
  }

  if (strcmp(argv[2], "-rle") != 0 && strcmp(argv[2], "-huff") != 0) {
    printf("Second argument must be -rle or -huff.\n");
    return false;
  }

  FILE *file = fopen(argv[3], "rb");
  if (file == NULL) {
    printf("Could not open input file: %s", argv[3]);
    return false;
  }
  fclose(file);

  return true;
}

int get_file_length(FILE *file) {
  // Safety check
  if (file == NULL) {
    return -1;
  }
  // Move to end of file (get pos), reset pointer to start
  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Cast to int and return
  return (int) length;
}

// AABBCC -> 2A2B2C
void rle_compress(FILE *file, int input_length, char *output_filename) {
  // struct for RLE
  typedef struct {
    int run_length;
    char character;
  } RunLengthChar;

  // temp array
  RunLengthChar *temp_arr = malloc(sizeof(RunLengthChar) * input_length);
  if (temp_arr == NULL) {
    return;
  }

  // get current char from file
  int current_char = fgetc(file);
  int next_char;

  // get next char from file
  int i = 0;
  int run_length = 1;

  // loop until end of file
  while ((next_char = fgetc(file)) != EOF) {
    if (current_char == next_char) {
      run_length++;
    } else {
      // store rle (i.e. 3A)
      temp_arr[i].run_length = run_length;
      temp_arr[i].character = current_char;

      // for array index
      i++;

      // reset run for new char
      run_length = 1;
    }

    // move loop along
    current_char = next_char;
  }

  // handle final run after loop
  temp_arr[i].character = current_char;
  temp_arr[i].run_length = run_length;
  i++;

  // open output file
  FILE *output_file = fopen(output_filename, "w");
  if (output_file == NULL) {
    printf("Could not open output file: %s\n", output_filename);
    return;
  }

  // print to file
  for (size_t j = 0; j < i; j++) {
    fprintf(output_file, "%i%c", temp_arr[j].run_length, temp_arr[j].character);
  }

  fclose(output_file);
  free(temp_arr);
}