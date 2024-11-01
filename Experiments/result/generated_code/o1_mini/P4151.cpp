#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Edge {
    int to;
    uint64_t val;
    struct Edge* next;
} Edge;

typedef struct {
    Edge** adj;
    bool* visited;
    uint64_t* xor_path;
    int N;
} Graph;

typedef struct {
    Edge* data;
    int size;
} Queue;

void enqueue(Queue* q, Edge* edge) {
    q->data[q->size++] = *edge;
}

bool dequeue(Queue* q, Edge* edge) {
    if (q->size == 0) return false;
    *edge = q->data[0];
    for(int i=1;i<q->size;i++) q->data[i-1] = q->data[i];
    q->size--;
    return true;
}

Graph* create_graph(int N) {
    Graph* g = malloc(sizeof(Graph));
    g->N = N;
    g->adj = calloc(N+1, sizeof(Edge*));
    g->visited = calloc(N+1, sizeof(bool));
    g->xor_path = calloc(N+1, sizeof(uint64_t));
    return g;
}

void add_edge(Graph* g, int u, int v, uint64_t w) {
    Edge* e1 = malloc(sizeof(Edge));
    e1->to = v;
    e1->val = w;
    e1->next = g->adj[u];
    g->adj[u] = e1;
    
    Edge* e2 = malloc(sizeof(Edge));
    e2->to = u;
    e2->val = w;
    e2->next = g->adj[v];
    g->adj[v] = e2;
}

uint64_t basis[64];

void insert_basis(uint64_t x) {
    for(int i=63;i>=0;i--){
        if((x>>i)&1){
            if(!basis[i]){
                basis[i] = x;
                break;
            }
            x ^= basis[i];
        }
    }
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    Graph* g = create_graph(N);
    for(int i=0;i<M;i++){
        int u, v;
        uint64_t w;
        scanf("%d %d %llu", &u, &v, &w);
        add_edge(g, u, v, w);
    }
    Queue q;
    q.data = malloc((N+1) * sizeof(Edge));
    q.size = 0;
    Edge start;
    start.to = 1;
    start.val = 0;
    enqueue(&q, &start);
    g->visited[1] = true;
    g->xor_path[1] = 0;
    while(dequeue(&q, &start)){
        int u = start.to;
        uint64_t val = start.val;
        for(Edge* e = g->adj[u]; e != NULL; e = e->next){
            int v = e->to;
            uint64_t nv = val ^ e->val;
            if(!g->visited[v]){
                g->visited[v] = true;
                g->xor_path[v] = nv;
                enqueue(&q, &(Edge){v, nv, NULL});
            }
            else{
                uint64_t cycle = g->xor_path[u] ^ e->val ^ g->xor_path[v];
                if(cycle != 0){
                    insert_basis(cycle);
                }
            }
        }
    }
    uint64_t res = g->xor_path[N];
    for(int i=63;i>=0;i--){
        if(basis[i] && (res ^ basis[i]) > res){
            res ^= basis[i];
        }
    }
    printf("%llu\n", res);
    // Free memory
    for(int i=1;i<=N;i++){
        Edge* e = g->adj[i];
        while(e){
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g->visited);
    free(g->xor_path);
    free(q.data);
    return 0;
}