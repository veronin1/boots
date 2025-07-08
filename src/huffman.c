#include <stdio.h>

typedef unsigned char byte;
typedef struct TreeNode {
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

void huffman_compress(FILE *input_file, int input_length,
                      const char *output_filename);