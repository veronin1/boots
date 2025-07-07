#ifndef RLE_H
#define RLE_H

#include <stdio.h>

void rle_compress(FILE *input_file, int input_length,
                  const char *output_filename);
void rle_decompress(FILE *input_file, int input_length,
                    const char *output_filename);

#endif