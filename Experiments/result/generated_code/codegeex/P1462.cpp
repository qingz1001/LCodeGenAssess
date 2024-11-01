#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 10001
#define MAXM 50001

struct Edge {
    int to;
    int cost;
};

struct Graph {
    struct Edge edges[MAXM];
    int n;
    int m;
};

void addEdge(struct Graph *graph, int from, int to, int cost) {
    graph->edges[graph->m].to = to;
    graph->edges[graph->m].cost = cost;
    graph->m++;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, m, b;
    scanf("%d %d %d", &n, &m, &b);

    struct Graph graph;
    graph.n = n;
    graph.m = 0;

    int fees[MAXN];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &fees[i]);
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(&graph, a, b, c);
        addEdge(&graph, b, a, c);
    }

    qsort(fees + 1, n, sizeof(int), compare);

    int left = 0, right = n - 1, result = INT_MAX;
    while (left <= right) {
        int mid = (left + right) / 2;
        int maxFee = fees[mid];
        int currentHealth = b;

        for (int i = 0; i < graph.m; i++) {
            if (graph.edges[i].cost > currentHealth) {
                maxFee = INT_MAX;
                break;
            }
            currentHealth -= graph.edges[i].cost;
        }

        if (maxFee != INT_MAX) {
            result = maxFee;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (result == INT_MAX) {
        printf("AFK\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}