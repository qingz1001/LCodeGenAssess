#include <stdio.h>
#include <stdlib.h>

#define MAXN 105

typedef struct {
    int to, weight;
} Edge;

typedef struct {
    int state, threshold;
    int inDegree;
    Edge edges[MAXN];
    int edgeCount;
} Node;

Node nodes[MAXN];
int n, p;

void topologicalSort() {
    int queue[MAXN], front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (nodes[i].inDegree == 0) {
            queue[rear++] = i;
        }
    }

    while (front < rear) {
        int u = queue[front++];
        for (int i = 0; i < nodes[u].edgeCount; i++) {
            int v = nodes[u].edges[i].to;
            int w = nodes[u].edges[i].weight;
            nodes[v].state += w * nodes[u].state;
            if (--nodes[v].inDegree == 0) {
                queue[rear++] = v;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &nodes[i].state, &nodes[i].threshold);
        nodes[i].edgeCount = 0;
        nodes[i].inDegree = 0;
    }

    for (int i = 0; i < p; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        nodes[u].edges[nodes[u].edgeCount].to = v;
        nodes[u].edges[nodes[u].edgeCount].weight = w;
        nodes[u].edgeCount++;
        nodes[v].inDegree++;
    }

    topologicalSort();

    int hasOutput = 0;
    for (int i = 1; i <= n; i++) {
        nodes[i].state -= nodes[i].threshold;
        if (nodes[i].state > 0) {
            printf("%d %d\n", i, nodes[i].state);
            hasOutput = 1;
        }
    }

    if (!hasOutput) {
        printf("NULL\n");
    }

    return 0;
}