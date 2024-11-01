#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 5005
#define MAX_M 50005

int N, M;
int graph[MAX_N][MAX_N];
int visited[MAX_N];
int stack[MAX_N], top;
int low[MAX_N], dfn[MAX_N], index;
int inStack[MAX_N];
int scc[MAX_N], sccCount;
int sccSize[MAX_N];

void tarjan(int u) {
    int v;
    low[u] = dfn[u] = ++index;
    stack[top++] = u;
    inStack[u] = 1;
    
    for (v = 1; v <= N; v++) {
        if (graph[u][v]) {
            if (!dfn[v]) {
                tarjan(v);
                if (low[v] < low[u]) low[u] = low[v];
            } else if (inStack[v] && dfn[v] < low[u]) {
                low[u] = dfn[v];
            }
        }
    }
    
    if (low[u] == dfn[u]) {
        sccCount++;
        do {
            v = stack[--top];
            inStack[v] = 0;
            scc[v] = sccCount;
            sccSize[sccCount]++;
        } while (v != u);
    }
}

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int i, j, a, b, t;
    int maxSize = 0, maxSCC = 0;
    
    scanf("%d %d", &N, &M);
    
    for (i = 0; i < M; i++) {
        scanf("%d %d %d", &a, &b, &t);
        graph[a][b] = 1;
        if (t == 2) graph[b][a] = 1;
    }
    
    for (i = 1; i <= N; i++) {
        if (!dfn[i]) tarjan(i);
    }
    
    for (i = 1; i <= sccCount; i++) {
        if (sccSize[i] > maxSize) {
            maxSize = sccSize[i];
            maxSCC = i;
        }
    }
    
    printf("%d\n", maxSize);
    
    int result[MAX_N], count = 0;
    for (i = 1; i <= N; i++) {
        if (scc[i] == maxSCC) {
            result[count++] = i;
        }
    }
    
    qsort(result, count, sizeof(int), cmp);
    
    for (i = 0; i < count; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    return 0;
}