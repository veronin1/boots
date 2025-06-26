#include <stdbool.h>
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

  FILE *file = fopen(argv[3], "r");

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
  return (int)length;
}

void rle_compress(FILE *file, int input_length, char *output) {
  if (file == NULL) {
    return;
  }

  char *buffer = malloc(input_length + 1);
  if (!buffer) {
    fprintf(stderr, "Memory allocation failed\n");
    return;
  }

  size_t bytes_read = fread(buffer, sizeof(char), input_length, file);
  buffer[bytes_read] = '\0';

  int i = 0;
  int output_index = 0;
  while (i < (int)bytes_read) {
    char current_char = buffer[i];
    int run_length = 1;

    // Count how many times current char repeats
    while (buffer[i] == buffer[i + 1]) {
      run_length++;
      i++;
    }

    if (run_length >= 3) {
      sprintf(output + output_index, "%i%c", run_length, current_char);
      output_index += strlen(output + output_index);
    } else {
      for (int j = 0; j < run_length; j++) {
        output[output_index++] = current_char;
      }
    }

    i++;
  }

  output[i] = '\0';

  // Write to output file
  FILE *output_file = fopen(output, "w");
  if (output_file != NULL) {
    fwrite(output, sizeof(char), 1, output_file);
  }

  fclose(output_file);
  free(buffer);
  return;
}