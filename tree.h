#ifndef TREE
#define TREE
#include <stdbool.h>

struct label_s {int weight; char content;};
typedef struct label_s label;

struct node_t {
    struct node_t* left_child;
    struct node_t* right_child;
    label* node_l;
};
typedef struct node_t* tree_t;
tree_t init_tree(char label_content, int label_weight);
tree_t merge_trees(tree_t left_child, tree_t right_child);
void print_rec_tree(tree_t t);
void print_tree(tree_t t);
void free_tree(tree_t t);
int tree_height(tree_t t);
int tree_size(tree_t t);
bool is_empty(tree_t t);

#endif 
