#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
struct graph_s {
    int nb_vertices;
    bool is_directed;
    int* degrees;
    int** neighbors;
};
typedef struct graph_s graph_t;

struct queue {
    int capacity;
    int size;
    int start;
    int* array;
}; typedef struct queue queue;

queue* init_queue(int n){
    queue* q = malloc(sizeof(queue));
    (*q).capacity=n;
    (*q).size=0;
    (*q).start=0;
    int* a = malloc(sizeof(int)*n);
    (*q).array = a;
    return q;
}

void enfiler(queue* q, int i){
    (*q).array[((*q).start+(*q).size)%((*q).capacity)]=i;
    (*q).size +=1;
}

int defiler(queue* q){
    int r = (*q).array[(*q).start];
    (*q).start=((*q).start +1)%(*q).capacity;
    (*q).size -= 1;
    return r;
}

bool is_empty(queue* q){
    return ((*q).size==0);
}

struct stack {
    int capacity;
    int size;
    int* array;
}; typedef struct stack stack;

stack* init_stack(int n){
    stack* s = malloc(sizeof(stack));
    int* a = malloc(sizeof(int)*n);
    (*s).capacity = n;
    (*s).size = 0;
    (*s).array=a;
    return s;
}

void enpiler(stack* s, int u){
    int n = (*s).size;
    (*s).array[n]=u;
    (*s).size ++;
}

int depiler(stack* s){
    (*s).size --;
    return (*s).array[(*s).size];
}

bool is_empty_stack(stack* s){
    return ((*s).size==0);
}

graph_t* init_graph(int n, bool is_directed){
    graph_t* g = malloc(sizeof(graph_t));
    (*g).nb_vertices = n;
    (*g).is_directed = is_directed;
    (*g).degrees = malloc(sizeof(int)*n);
    (*g).neighbors = malloc(sizeof(int*)*n);
    for (int i=0; i<n;i++){
        (*g).neighbors[i]= malloc(sizeof(int)*n);
    }
    return g;
}

void free_graph(graph_t* g){
    for (int i=0; i<(*g).nb_vertices;i++){
        free((*g).neighbors[i]);
    }
    free((*g).neighbors);
    free((*g).degrees);
    free(g);
}

bool are_adjacent(graph_t* g,int i, int j){
    for (int k =0; k<(*g).degrees[i];k++){
        if ((*g).neighbors[i][k]==j){
            return true;
        }
    }
    return false ;
}

void add_edge(graph_t* g, int i,int j){
    if (!(are_adjacent(g,i,j))){
        (*g).degrees[i]++;
        int n = (*g).degrees[i];
        int* neighbor = malloc(sizeof(int)*n);
        for (int k=0; k<n-1;k++){
            neighbor[k]=(*g).neighbors[i][k];
        }
        neighbor[n-1]=j;
        (*g).neighbors[i]=neighbor;
    }
}

void remove_edge(graph_t* g,int i, int j){
    if (are_adjacent(g,i,j)){
        (*g).degrees[i]--;
        int n = (*g).degrees[i];
        int* neighbor = malloc(sizeof(int)*n);
        int l = 0 ;
        while (((*g).neighbors[i][l])!=j){
            neighbor[l]=(*g).neighbors[i][l];
            l++;
        }
        l++;
        while (l<n){
            neighbor[l-1]=(*g).neighbors[i][l];
            l++;
        }
        (*g).neighbors[i]=neighbor;
    }
}

void breadth_first_search(graph_t* g, int v){
    int n = (*g).nb_vertices;
    bool* vus = malloc(sizeof(bool)*n);
    for (int i=0;i<n;i++){
        vus[i]=false;
    }
    queue* q = init_queue(n);
    enfiler(q,v);
    while(!(is_empty(q))){
        int w = defiler(q);
        if(!(vus[w])){
            vus[w]=true;
            printf("%d\n",w);
            for(int i=0; i<(*g).degrees[w];i++){
                enfiler(q,(*g).neighbors[w][i]);
            }
        }
    }
}

void depth_first_search(graph_t* g, int v){
    int n = (*g).nb_vertices;
    bool* vus = malloc(sizeof(bool)*n);
    for (int i=0;i<n;i++){
        vus[i]=false;
    }
    stack* s = init_stack(n);
    enpiler(s,v);
    while(!(is_empty_stack(s))){
        int w = depiler(s);
        if(!(vus[w])){
            vus[w]=true;
            printf("%d\n",w);
            for(int i=0; i<(*g).degrees[w];i++){
                enpiler(s,(*g).neighbors[w][i]);
            }
        }
    }
}

void depth_first_search_aux(graph_t* g, bool* vus, int w){
    if (!(vus[w])){
        vus[w]=true;
        printf("%d\n",w);
        for (int i=0; i<(*g).degrees[w];i++){
            depth_first_search_aux(g,vus,(*g).neighbors[w][i]);
        }
    }
}

void depth_first_search_rec(graph_t* g, int v){
    int n = (*g).nb_vertices;
    bool* vus = malloc(sizeof(bool)*n);
    for (int i=0;i<n;i++){
        vus[i]=false;
    }
    depth_first_search_aux(g,vus,v);
}

void get_path(graph_t* g,int i, int j){
    int n = (*g).nb_vertices;
    int* pred = malloc(sizeof(int)*n);
    bool* vus = malloc(sizeof(bool)*n);
    for (int i=0;i<n;i++){
        vus[i]=false;
    }
    queue* q = init_queue(n);
    enfiler(q,i);
    while(!(is_empty(q))){
        int w = defiler(q);
        if(!(vus[w])){
            vus[w]=true;
            for(int i=0; i<(*g).degrees[w];i++){
                enfiler(q,(*g).neighbors[w][i]);
                pred[(*g).neighbors[w][i]]=w;
            }
        }
    }
    pred[i]=-1;
    int current = j;
    while (current!=-1){
        printf("%d\n", current);
        current = pred[current];
    }
}


int main(){
    graph_t* g = init_graph(5,false);
    add_edge(g,0,2);
    add_edge(g,2,3);
    add_edge(g,2,4);
    add_edge(g,3,0);
    add_edge(g,4,1);
    get_path(g,0,1);
}