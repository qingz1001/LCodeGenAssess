#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define MAXN 50005
#define MAXM 100000
#define MAX_BITS 60

typedef struct Edge {
    int to;
    uint64_t weight;
    struct Edge* next;
} Edge;

Edge* graph[MAXN];
uint64_t basis[MAX_BITS];
uint64_t value[MAXN];
int visited[MAXN];
int N, M;

void add_edge(int u, int v, uint64_t w){
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
}

int insert_basis(uint64_t x){
    for(int i = MAX_BITS-1;i >=0;i--){
        if((x>>i)&1){
            if(!basis[i]){
                basis[i] = x;
                return 1;
            }
            x ^= basis[i];
        }
    }
    return 0;
}

void dfs(int u){
    visited[u] = 1;
    for(Edge* e = graph[u]; e != NULL; e = e->next){
        int v = e->to;
        uint64_t w = e->weight;
        if(!visited[v]){
            value[v] = value[u] ^ w;
            dfs(v);
        }
        else{
            uint64_t cycle = value[u] ^ value[v] ^ w;
            if(cycle){
                insert_basis(cycle);
            }
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int i=0;i<M;i++){
        int S, T;
        uint64_t D;
        scanf("%d %d %llu", &S, &T, &D);
        add_edge(S, T, D);
        add_edge(T, S, D);
    }
    memset(basis, 0, sizeof(basis));
    memset(visited, 0, sizeof(visited));
    value[1] = 0;
    dfs(1);
    uint64_t res = value[N];
    for(int i=MAX_BITS-1;i>=0;i--){
        if(basis[i] && (res ^ basis[i]) > res){
            res ^= basis[i];
        }
    }
    printf("%llu\n", res);
    return 0;
}