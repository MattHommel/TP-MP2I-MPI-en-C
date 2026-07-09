#include "immutable_int_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int_list_t empty_list(){
    return NULL;
}

int list_head(int_list_t l){
    if (l==NULL){
        return (-1);
    }
    else {
        return (*l).head;
    }
}

int_list_t list_tail(int_list_t l){
    if (l==NULL){
        return NULL;
    }
    else {
        return (*l).tail;
    }
}

int_list_t cons(int_list_t l, int h){
    int_list_t r = malloc(sizeof(int_list_t));
    (*r).head = h;
    (*r).tail = l;
    return r ;
}

bool is_empty(int_list_t l){
    if (l==NULL){
        return true;
    }
    else{
        return false;
    }
}

int list_length(int_list_t l){
    int n = 0;
    int_list_t i = l;
    while (!(is_empty(i))){
        n++;
        i=list_tail(i);
    }
    return n;
}

bool is_in_list(int_list_t l, int e){
    int_list_t i = l;
    while (!(is_empty(i))){
        if (list_head(i)==e){
            return true;
        }
        else {
            i=list_tail(i);
        }
    }
    return false;
}

void print_list(int_list_t l){
    if (!(is_empty(l))) {
        if(list_tail(l)==NULL){
            printf("%d\n",list_head(l));
        }
        else{printf("%d, ",list_head(l));}
        print_list(list_tail(l));
    }
}

int_list_t reverse(int_list_t l){
    int_list_t r = empty_list();
    int_list_t current = l;
    while ((*current).tail!=NULL) {
        r=cons(r,list_head(current));
        current =list_tail(current);
    }
    r=cons(r,list_head(current));
    return r;
}

int_list_t list_concatenate(int_list_t l1, int_list_t l2){
    int_list_t l3 = l2;
    int_list_t rev_l1 = reverse(l1);
    for (int i=0;i<list_length(l1);i++){
        l3=cons(l3,list_head(rev_l1));
        rev_l1 = list_tail(rev_l1);
    }
    return l3;
}