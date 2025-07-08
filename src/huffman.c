#include <stdio.h>
#include <stdlib.h>

#define MAX 256

typedef unsigned char byte;

// Tree node for Huffman
typedef struct TreeNode {
  byte value;
  int frequency;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

// Priority queue element
typedef struct {
  TreeNode *node;
  int priority;
} PriorityQueue;

PriorityQueue *queue[MAX];
int queue_size = 0;

// Insert into priority queue (sorted by priority, lowest first)
void insert(TreeNode *node, int priority) {
  if (queue_size >= MAX) {
    printf("Queue full\n");
    return;
  }

  PriorityQueue *item = malloc(sizeof(PriorityQueue));
  item->node = node;
  item->priority = priority;

  int i = queue_size - 1;
  while (i >= 0 && queue[i]->priority > priority) {
    queue[i + 1] = queue[i];
    i--;
  }

  queue[i + 1] = item;

  queue_size++;
}

// pop from priority queue (lowest prior)
PriorityQueue *pop() {
  if (queue_size == 0) return NULL;
  return queue[--queue_size];
}

void huffman_compress(FILE *input_file, int input_length, const char *output_filename) {
  // freq table
  byte *frequencyTable = malloc(sizeof(byte) * MAX);
  if (frequencyTable == NULL) {
    printf("Memory allocation failed: frequencyTable");
    return;
  }

  // zero out data
  for (int i = 0; i < MAX; i++) {
    frequencyTable[i] = 0;
  }

  // read bytes and count frequency
  byte b;
  while (fread(&b, 1, 1, input_file) == 1) {
    frequencyTable[b]++;
  }

  for (int i = 0; i < MAX; i++) {
    if (frequencyTable[i] > 0) {
      TreeNode *node = malloc(sizeof(TreeNode));
      node->value = (byte) i;
      node->frequency = frequencyTable[i];
      node->left = NULL;
      node->right = NULL;

      insert(node, frequencyTable[i]);
    }
  }

  return;
}
