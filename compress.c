#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool argument_check(int argc, char *argv[]);

int main(int argc, char *argv[]) {
  if (!argument_check(argc, argv)) {
    return 1;
  }

  char *test_literal = "AAAABBBAABBBBBCCCCCCCDABCDBAAABBBBCCCD";
  char test[100];
  strcpy(test, test_literal);
  char rle[200];

  int i = 0;
  int rle_index = 0;
  while (test[i] != '\0') {
    char current_char = test[i];
    int run_length = 1;

    // Count how many times current char repeats
    while (test[i] == test[i + 1]) {
      run_length++;
      i++;
    }

    if (run_length >= 3) {
      sprintf(rle + rle_index, "%i%c", run_length, current_char);
      rle_index += strlen(rle + rle_index);
    }

    i++;
  }

  rle[i] = '\0';

  for (int i = 0, n = strlen(rle); i < n; i++) {
    printf("%c", rle[i]);
  }

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

// void rle_compress(FILE *fp, int input_length, char *output);