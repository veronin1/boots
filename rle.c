#include "rle.h"

#include <stdio.h>
#include <stdlib.h>

// struct for RLE
typedef unsigned char byte;
typedef struct {
  byte run_length;
  byte character;
} RunLengthChar;

// AABBCC -> 2A2B2C
void rle_compress(FILE *file, int input_length, const char *output_filename) {
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
      if (run_length >= 3) {
        temp_arr[i].run_length = run_length;
        temp_arr[i].character = prev;
        i++;
      } else {
        for (int i = 0; i < run_length; i++) {
          temp_arr[i].character = prev;
          temp_arr[i].run_length = 1;
          i++;
        }
      }
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

// 2A2B2C -> AABBCC
void rle_decompress(FILE *file, int input_length, const char *output_filename) {
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