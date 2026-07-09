#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct graph_s{
    int nb_vertices;
    bool is_directed;
    bool* edge_matrix;
    int* weight_matrix;
};

typedef struct graph_s graph_t;

graph_t* init_graph(int n, bool is_directed){
    graph_t* g = malloc(sizeof(graph_t));
    (*g).nb_vertices = n;
    (*g).is_directed = is_directed;
    (*g).edge_matrix = malloc(sizeof(bool)*n*n);
    (*g).weight_matrix = malloc(sizeof(int)*n*n);
    return g;
}

void free_graph(graph_t* g){
    free((*g).edge_matrix);
    free((*g).weight_matrix);
    free(g);
}

void add_edge(graph_t* g, int i, int j, int w){
    if (!((*g).is_directed)){
        (*g).edge_matrix[j*((*g).nb_vertices)+i]= true;
        (*g).weight_matrix[j*((*g).nb_vertices)+i]=w;
    }
    (*g).edge_matrix[i*((*g).nb_vertices)+j]= true;
    (*g).weight_matrix[i*((*g).nb_vertices)+j]=w;
}

void remove_edge(graph_t* g, int i, int j){
    if (!((*g).is_directed)){
        (*g).edge_matrix[j*((*g).nb_vertices)+i]= false;
    }
    (*g).edge_matrix[i*((*g).nb_vertices)+j]= false;
}

bool are_adjacent(graph_t* g, int i, int j){
    return (*g).edge_matrix[i*((*g).nb_vertices)+j];
}

int wieght(graph_t* g, int i, int j){
    return (*g).weight_matrix[i*((*g).nb_vertices)+j];
}

void floyd_warshall(graph_t* g, int* dist, int* next){
    int n = (*g).nb_vertices ;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if ((*g).edge_matrix[i*n+j]) {
                dist[i*n+j]=(*g).weight_matrix[i*n+j];
            }
            else {
                dist[i*n+j]=999;
            }
        }
    }
    for (int k = 0; k < n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (dist[i*n+k] + dist[k*n+j] < dist[i*n+j]) {
                    dist[i*n+j] = dist[i*n+k] + dist[k*n+j];
                    next[i*n+j] = k;
                }
            }
        }
    }
}

void print_matrix(int* m, int n){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d, ", m[i*n+j]);
        }
        printf("\n");
    }
}

int main(){
    graph_t* g = init_graph(5,true);
    add_edge(g,0,2,9);
    add_edge(g,0,1,2);
    add_edge(g,3,2,1);
    add_edge(g,1,3,1);
    int* d1 = malloc(sizeof(int)*((*g).nb_vertices)*((*g).nb_vertices));
    int* d2 = malloc(sizeof(int)*((*g).nb_vertices)*((*g).nb_vertices));
    floyd_warshall(g,d1,d2);
    print_matrix(d1,(*g).nb_vertices);
    print_matrix(d2,(*g).nb_vertices);
    return -1;
}