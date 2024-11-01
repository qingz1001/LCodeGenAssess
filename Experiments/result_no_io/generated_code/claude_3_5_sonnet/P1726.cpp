#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 5005
#define MAXM 50005

int N, M;
int graph[MAXN][MAXN];
int visited[MAXN];
int stack[MAXN], top;
int low[MAXN], dfn[MAXN], scc[MAXN], in_stack[MAXN];
int scc_count, time_stamp;
int scc_size[MAXN];
int max_scc_size, max_scc_id;

void tarjan(int u) {
    int v;
    low[u] = dfn[u] = ++time_stamp;
    stack[top++] = u;
    in_stack[u] = 1;
    
    for (v = 1; v <= N; v++) {
        if (graph[u][v]) {
            if (!dfn[v]) {
                tarjan(v);
                if (low[v] < low[u]) low[u] = low[v];
            } else if (in_stack[v] && dfn[v] < low[u]) {
                low[u] = dfn[v];
            }
        }
    }
    
    if (low[u] == dfn[u]) {
        scc_count++;
        do {
            v = stack[--top];
            in_stack[v] = 0;
            scc[v] = scc_count;
            scc_size[scc_count]++;
            if (scc_size[scc_count] > max_scc_size || 
                (scc_size[scc_count] == max_scc_size && scc_count < max_scc_id)) {
                max_scc_size = scc_size[scc_count];
                max_scc_id = scc_count;
            }
        } while (v != u);
    }
}

int main() {
    int i, j, a, b, t;
    
    scanf("%d %d", &N, &M);
    
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &t);
        graph[a][b] = 1;
        if (t == 2) graph[b][a] = 1;
    }
    
    for (i = 1; i <= N; i++) {
        if (!dfn[i]) tarjan(i);
    }
    
    printf("%d\n", max_scc_size);
    
    for (i = 1; i <= N; i++) {
        if (scc[i] == max_scc_id) {
            printf("%d ", i);
        }
    }
    
    return 0;
}