#ifndef IMMUTABLE_LIST
#define IMMUTABLE_LIST
#include <stdbool.h>
struct cell_s {
    int head;
    struct cell_s* tail;
};
typedef struct cell_s cell_t ;
typedef cell_t* int_list_t ;

int_list_t empty_list();

int list_head(int_list_t l);

int_list_t list_tail(int_list_t l);

int_list_t cons(int_list_t l, int h);

bool is_empty(int_list_t l);

int list_length(int_list_t l);

bool is_in_list(int_list_t l, int e);

void print_list(int_list_t l);

int_list_t reverse(int_list_t l);

int_list_t list_concatenate(int_list_t l1, int_list_t l2);

#endif