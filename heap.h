#ifndef HEAP
#define HEAP
#include "tree.h"
#include <stdbool.h>

struct heap_s {int* priority; tree_t* labels; int capacity;int size;};
typedef struct heap_s heap_t;

heap_t init_heap(int capacity);
void free_heap(heap_t h);
int sift_up(heap_t* heap, int index);
void insert_heap(tree_t value, int priority, heap_t* heap);
void swap(heap_t* heap, int i, int j);
int sift_down(heap_t* heap, int index);
tree_t extract_heap(heap_t* heap);
bool heap_is_empty(heap_t h);
void sort(int* a, int a_size);


#endif