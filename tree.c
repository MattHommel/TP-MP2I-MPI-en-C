#implémentation d'arbre pour l'algorithme de Huffman 

#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int max(int x,int y){
    if (x>y){return x;}
    else {return y;}
}

tree_t init_tree(char label_content, int label_weight){
    tree_t t = malloc(sizeof(struct node_t));
    t->node_l = malloc(sizeof(label));
    (t->node_l)->weight = label_weight;
    (t->node_l)->content = label_content;
    t->left_child = NULL;
    t->right_child = NULL;
    return t;
}

tree_t merge_trees(tree_t left_child, tree_t right_child){
    tree_t t = malloc(sizeof(struct node_t));
    t->node_l = malloc(sizeof(label));
    (t->node_l)->weight = left_child->node_l->weight + right_child->node_l->weight;
    (t->node_l)->content = '\0';
    t->left_child = left_child;
    t->right_child = right_child;
    return t;
}

void print_rec_tree(tree_t t){
    if(t->left_child==NULL && t->right_child == NULL){
        printf("(%c,%d,0)", t->node_l->content, t->node_l->weight);
    }
    else{
        print_rec_tree(t->left_child);
        print_rec_tree(t->right_child);
        printf("( ,%d,2)", t->node_l->weight);
    }
}

void print_tree(tree_t t){
  print_rec_tree(t);
  printf("\n");
}

void free_tree(tree_t t){
    if(t->left_child!=NULL){
        free_tree(t->left_child);
    }
    if(t->right_child!=NULL){
        free_tree(t->right_child);
    }
    free(t->node_l);
    free(t);
}

int tree_height(tree_t t){
    if(t == NULL){
        return -1;
    }
    else{
        return max(tree_height(t->left_child),tree_height(t->right_child))+1;
    }
}

int tree_size(tree_t t){
    if(t == NULL){
        return 0;
    }
    else{
        return tree_size(t->left_child)+tree_size(t->right_child)+1;
    }
}

int main(){
    tree_t t = merge_trees(init_tree('a',4),merge_trees(init_tree('b',3),init_tree('c',5)));
    print_tree(t);
    printf("%d, %d",tree_height(t),tree_size(t));
    return -1;
}
