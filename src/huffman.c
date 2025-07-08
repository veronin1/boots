#include <stdio.h>
#include <stdlib.h>

#define MAX 256

typedef unsigned char byte;
typedef struct TreeNode {
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

void huffman_compress(FILE *input_file, int input_length, const char *output_filename) {
  // freq table
  byte *frequencyTable = malloc(sizeof(byte) * 256);
  if (frequencyTable == NULL) {
    printf("Memory allocation failed: frequencyTable");
    return;
  }

  // zero out data
  for (int i = 0; i < 256; i++) {
    frequencyTable[i] = 0;
  }

  // read bytes and count frequency
  byte b;
  while (fread(&b, 1, 1, input_file) == 1) {
    frequencyTable[b]++;
  }

  typedef struct {
    byte item;
    int priority;
  } PriorityQueue;

  PriorityQueue *queue[MAX];

  return;
}