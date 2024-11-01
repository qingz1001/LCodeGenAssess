#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Edge {
    int to;
    struct Edge *next;
} Edge;

Edge *adj[100001];
int inDegree[100001];
int outDegree[100001];
int visited[100001];
int n, m;

void addEdge(int u, int v) {
    Edge *newEdge = (Edge *)malloc(sizeof(Edge));
    newEdge->to = v;
    newEdge->next = adj[u];
    adj[u] = newEdge;
    inDegree[v]++;
    outDegree[u]++;
}

void dfs(int u, int *maxDepth, int *minDepth) {
    visited[u] = 1;
    for (Edge *e = adj[u]; e != NULL; e = e->next) {
        if (!visited[e->to]) {
            dfs(e->to, maxDepth, minDepth);
            *maxDepth = (*maxDepth > outDegree[u] + inDegree[u]) ? *maxDepth : outDegree[u] + inDegree[u];
            *minDepth = (*minDepth < outDegree[u] + inDegree[u]) ? outDegree[u] + inDegree[u] : *minDepth;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }

    int maxMaskClasses = INT_MIN, minMaskClasses = INT_MAX;
    for (int i = 1; i <= n; i++) {
        if (inDegree[i] == 0 && outDegree[i] == 0) {
            printf("-1 -1\n");
            return 0;
        }
        if (inDegree[i] == 0 || outDegree[i] == 0) {
            if (maxMaskClasses == INT_MIN) {
                maxMaskClasses = outDegree[i] + inDegree[i];
                minMaskClasses = outDegree[i] + inDegree[i];
            } else {
                maxMaskClasses = (maxMaskClasses > outDegree[i] + inDegree[i]) ? maxMaskClasses : outDegree[i] + inDegree[i];
                minMaskClasses = (minMaskClasses < outDegree[i] + inDegree[i]) ? minMaskClasses : minMaskClasses;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            int maxDepth = 0, minDepth = 0;
            dfs(i, &maxDepth, &minDepth);
            maxMaskClasses = (maxMaskClasses > maxDepth) ? maxMaskClasses : maxDepth;
            minMaskClasses = (minMaskClasses < minDepth) ? minMaskClasses : minMaskClasses;
        }
    }

    if (maxMaskClasses == INT_MIN || minMaskClasses == INT_MAX) {
        printf("-1 -1\n");
    } else {
        printf("%d %d\n", maxMaskClasses, minMaskClasses);
    }

    return 0;
}