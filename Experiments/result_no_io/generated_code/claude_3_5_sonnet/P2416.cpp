#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 300005
#define MAX_M 300005

typedef struct Edge {
    int to;
    int has_puff;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
bool visited[MAX_N];
bool has_puff_path;

void add_edge(int from, int to, int has_puff) {
    Edge* e = (Edge*)malloc(sizeof(Edge));
    e->to = to;
    e->has_puff = has_puff;
    e->next = graph[from];
    graph[from] = e;
}

void dfs(int current, int target, bool found_puff) {
    if (current == target && found_puff) {
        has_puff_path = true;
        return;
    }
    
    visited[current] = true;
    
    for (Edge* e = graph[current]; e != NULL; e = e->next) {
        if (!visited[e->to]) {
            dfs(e->to, target, found_puff || e->has_puff);
        }
    }
}

int main() {
    int N, M, Q;
    scanf("%d %d", &N, &M);
    
    for (int i = 0; i < M; i++) {
        int X, Y, Z;
        scanf("%d %d %d", &X, &Y, &Z);
        add_edge(X, Y, Z);
        add_edge(Y, X, Z);
    }
    
    scanf("%d", &Q);
    
    for (int i = 0; i < Q; i++) {
        int S, T;
        scanf("%d %d", &S, &T);
        
        memset(visited, 0, sizeof(visited));
        has_puff_path = false;
        
        dfs(S, T, false);
        
        printf("%s\n", has_puff_path ? "YES" : "NO");
    }
    
    return 0;
}