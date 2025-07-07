#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "rle.h"

bool argument_check(int argc, char *argv[]);
int get_file_length(FILE *file);

int main(int argc, char *argv[]) {
  if (!argument_check(argc, argv)) {
    return 1;
  }

  FILE *file = fopen(argv[3], "rb");

  int length = get_file_length(file);

  if (strcmp(argv[1], "-c") == 0) {
    rle_compress(file, length, argv[4]);
  } else if (strcmp(argv[1], "-d") == 0) {
    rle_decompress(file, length, argv[4]);
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