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

void walkHuffman(TreeNode *node, char path[], int depth);

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
  PriorityQueue *item = queue[0];

  for (int i = 1; i < queue_size; i++) {
    queue[i - 1] = queue[i];
  }
  queue_size--;
  return item;
}

void huffman_compress(FILE *input_file, int input_length, const char *output_filename) {
  // freq table
  int frequencyTable[MAX] = {0};

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

  while (queue_size > 1) {
    TreeNode *node = malloc(sizeof(TreeNode));
    PriorityQueue *first = pop();
    PriorityQueue *second = pop();

    node->frequency = first->priority + second->priority;
    node->left = first->node;
    node->right = second->node;
    node->value = 0;

    insert(node, node->frequency);

    free(first);
    free(second);
  }

  if (queue_size > 0 && queue[0] != NULL) {
    char path[MAX];
    walkHuffman(queue[0]->node, path, 0);
  }
}

char *codes[MAX];

void walkHuffman(TreeNode *node, char path[], int depth) {
  if (!node->right && !node->left) {
    codes[node->value] = malloc(depth + 1);

    for (int i = 0; i < depth; i++) {
      codes[node->value][i] = path[i];
    }
    codes[node->value][depth] = '\0';
  }

  if (node->left) {
    path[depth] = '0';
    walkHuffman(node->left, path, depth + 1);
  }
  if (node->right) {
    path[depth] = '1';
    walkHuffman(node->right, path, depth + 1);
  }
}
