#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool argument_check(int argc, char *argv[]);
void rle_compress(FILE *fp, int input_length, char *output);
void rle_decompress(FILE *file, int input_length, char *output_filename);
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

// struct for RLE
typedef unsigned char byte;
typedef struct {
  byte run_length;
  byte character;
} RunLengthChar;

// AABBCC -> 2A2B2C
void rle_compress(FILE *file, int input_length, char *output_filename) {
  // reset file pointer to read from beginning (just in case)
  fseek(file, 0, SEEK_SET);

  // temp array
  RunLengthChar *temp_arr = malloc(sizeof(RunLengthChar) * input_length);
  if (temp_arr == NULL) {
    return;
  }

  byte prev;
  byte next;
  int i = 0;
  int run_length = 1;

  // read one byte into prev
  fread(&prev, sizeof(byte), 1, file);

  // Read characters until EOF, count consecutive repeats, and save runs when
  // the character changes.
  while (fread(&next, sizeof(byte), 1, file) == 1) {
    if (next == prev) {
      run_length++;
    } else {
      temp_arr[i].run_length = run_length;
      temp_arr[i].character = prev;
      i++;
      run_length = 1;
    }
    prev = next;
  }

  // handle final run after loop
  temp_arr[i].character = prev;
  temp_arr[i].run_length = run_length;
  i++;

  // open output file
  FILE *output_file = fopen(output_filename, "wb");
  if (output_file == NULL) {
    printf("Could not open output file: %s\n", output_filename);
    return;
  }

  // print to file
  for (size_t j = 0; j < i; j++) {
    fwrite(&temp_arr[j].run_length, sizeof(byte), 1, output_file);
    fwrite(&temp_arr[j].character, sizeof(byte), 1, output_file);
  }

  fclose(output_file);
  free(temp_arr);
}

void rle_decompress(FILE *file, int input_length, char *output_filename) {
  fseek(file, 0, SEEK_SET);

  FILE *output_file = fopen(output_filename, "w");

  byte run_length;
  byte character;

  while (fread(&run_length, sizeof(byte), 1, file) == 1) {
    if (fread(&character, sizeof(byte), 1, file) != 1) {
      break;
    }

    for (int i = 0; i < run_length; i++) {
      fwrite(&character, sizeof(byte), 1, output_file);
    }
  }
}