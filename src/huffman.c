#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;
typedef struct TreeNode {
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

void huffman_compress(FILE *input_file, int input_length,
                      const char *output_filename) {
  byte *frequencyTable = malloc(sizeof(byte) * 256);
  if (frequencyTable == NULL) {
    printf("Memory allocation failed: frequencyTable");
    return;
  }
  return;
}