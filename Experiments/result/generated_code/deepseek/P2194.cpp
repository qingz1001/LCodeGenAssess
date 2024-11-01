#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

typedef struct {
    int v;
    struct Edge* next;
} Edge;

typedef struct {
    Edge* head;
} Node;

Node* graph;
int* cost;
int* visited;
int* low;
int* disc;
int* stack;
int* inStack;
int* sccCost;
int* sccCount;
int time, top, sccIndex;

void addEdge(int u, int v) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->v = v;
    newEdge->next = graph[u].head;
    graph[u].head = newEdge;
}

void tarjan(int u) {
    disc[u] = low[u] = ++time;
    stack[++top] = u;
    inStack[u] = 1;

    for (Edge* e = graph[u].head; e != NULL; e = e->next) {
        int v = e->v;
        if (disc[v] == -1) {
            tarjan(v);
            if (low[v] < low[u]) low[u] = low[v];
        } else if (inStack[v] && disc[v] < low[u]) {
            low[u] = disc[v];
        }
    }

    if (disc[u] == low[u]) {
        int minCost = cost[u];
        int count = 1;
        while (1) {
            int v = stack[top--];
            inStack[v] = 0;
            if (cost[v] < minCost) {
                minCost = cost[v];
                count = 1;
            } else if (cost[v] == minCost) {
                count++;
            }
            if (v == u) break;
        }
        sccCost[sccIndex] = minCost;
        sccCount[sccIndex++] = count;
    }
}

int main() {
    int n, m;
    scanf("%d", &n);
    cost = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &cost[i]);
    }

    scanf("%d", &m);
    graph = (Node*)malloc(n * sizeof(Node));
    for (int i = 0; i < n; i++) {
        graph[i].head = NULL;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u - 1, v - 1);
    }

    visited = (int*)malloc(n * sizeof(int));
    low = (int*)malloc(n * sizeof(int));
    disc = (int*)malloc(n * sizeof(int));
    stack = (int*)malloc(n * sizeof(int));
    inStack = (int*)malloc(n * sizeof(int));
    sccCost = (int*)malloc(n * sizeof(int));
    sccCount = (int*)malloc(n * sizeof(int));

    memset(visited, 0, n * sizeof(int));
    memset(low, -1, n * sizeof(int));
    memset(disc, -1, n * sizeof(int));
    memset(inStack, 0, n * sizeof(int));

    time = 0;
    top = -1;
    sccIndex = 0;

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            tarjan(i);
        }
    }

    long long totalCost = 0;
    long long totalCount = 1;
    for (int i = 0; i < sccIndex; i++) {
        totalCost += sccCost[i];
        totalCount = (totalCount * sccCount[i]) % MOD;
    }

    printf("%lld %lld\n", totalCost, totalCount);

    free(cost);
    free(visited);
    free(low);
    free(disc);
    free(stack);
    free(inStack);
    free(sccCost);
    free(sccCount);
    for (int i = 0; i < n; i++) {
        Edge* e = graph[i].head;
        while (e != NULL) {
            Edge* next = e->next;
            free(e);
            e = next;
        }
    }
    free(graph);

    return 0;
}