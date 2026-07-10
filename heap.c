#include "heap.h"
#include "tree.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

heap_t init_heap(int capacity){
    heap_t h ;
    h.size=0;
    h.capacity = capacity;
    h.labels = malloc(sizeof(tree_t)*capacity);
    h.priority = malloc(sizeof(int)*capacity);
    for (int i =0; i<capacity;i++){
        h.priority[i]=0;
        h.labels[i]=NULL;
    }
    return h;
}

void free_heap(heap_t h){
    free(h.priority);
    free(h.labels);
}

int sift_up(heap_t* heap, int index){
    int p =(heap->priority)[index];
    tree_t v = (heap->labels)[index];
    int parent_pos = (index-1)/2;
    int p_parent = (heap->priority)[parent_pos];
    if (p>p_parent){
        return index;
    }
    else {
        heap->priority[index]=p_parent;
        heap->labels[index]=heap->labels[parent_pos];
        heap->priority[parent_pos]=p;
        heap->labels[parent_pos]=v;
        return (index-1)/2;
    }
}

void insert_heap(tree_t value, int priority, heap_t* heap){
    int current_pos = heap->size;
    heap->priority[current_pos]=priority;
    heap->labels[current_pos]=value;
    heap->size ++;
    while (current_pos!=sift_up(heap,current_pos)&&current_pos!=0){
        current_pos=sift_up(heap,current_pos);
    }
}

void swap(heap_t* heap, int i, int j){
    int x = (heap->priority)[i];
    tree_t y = (heap->labels)[i];
    (heap->priority)[i]=(heap->priority)[j];
    (heap->labels)[i]=(heap->labels)[j];
    (heap->priority)[j]=x;
    (heap->labels)[j]=y;
}

int sift_down(heap_t* heap, int index){
    int prio =(heap->priority)[index];
    tree_t v = (heap->labels)[index];
    int childleft = 2*index +1;
    int childright = 2*index +2;
    if (childleft>=heap->size){
        return index;
    }
    else if(childright>=heap->size){
        if((heap->priority)[childleft]<prio){
            swap(heap,index,childleft);
            return childleft;
        }
        else{
            swap(heap,index,childright);
            return childright;
        }
    }
    else{
        int m = childleft;
        if ((heap->priority)[childleft]>(heap->priority)[childright]){
            m=childright;
        }
        if((heap->priority)[m]<prio){
            swap(heap,index,m);
            return m;
        }
        else{
            return index;
        }
    }
}

tree_t extract_heap(heap_t* heap){
    tree_t result = heap->labels[0];
    heap->labels[0]=heap->labels[heap->size-1];
    heap->priority[0]=heap->priority[heap->size-1];
    heap->size --;
    int current_pos = 0;
    while (current_pos!=sift_down(heap,current_pos)){
        current_pos=sift_down(heap,current_pos);
    }
    return result;
}

bool heap_is_empty(heap_t h){
    return (h.size==0);
}

void sort(int* a, int a_size){
    heap_t* h;
    heap_t h_ = init_heap(a_size);
    h=&h_;
    for (int i=0; i<a_size;i++){
        insert_heap(init_tree('\0',a[i]),a[i],h);
    }
    for (int i=0; i<a_size;i++){
        a[i]=extract_heap(h)->node_l->weight;
    } 
}

int main(){
    return -1;
}