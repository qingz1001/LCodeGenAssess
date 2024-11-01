#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000
#define MAXM 5000

typedef struct {
    int i, j, b;
} Constraint;

int n, m;
Constraint constraints[MAXM];
int dist[MAXN + 1];

int bellman_ford() {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }
    dist[1] = 0;

    for (int k = 1; k <= n - 1; k++) {
        for (int i = 0; i < m; i++) {
            int u = constraints[i].i;
            int v = constraints[i].j;
            int w = constraints[i].b;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int u = constraints[i].i;
        int v = constraints[i].j;
        int w = constraints[i].b;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            return 0; // Negative cycle detected
        }
    }

    return 1; // No negative cycle
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &constraints[i].i, &constraints[i].j, &constraints[i].b);
    }

    if (bellman_ford()) {
        int min_dist = INT_MAX;
        for (int i = 1; i <= n; i++) {
            if (dist[i] < min_dist) {
                min_dist = dist[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            printf("%d\n", dist[i] - min_dist);
        }
    } else {
        printf("NO SOLUTION\n");
    }

    return 0;
}