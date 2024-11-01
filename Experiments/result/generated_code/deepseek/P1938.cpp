#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_CITIES 220
#define MAX_PATHS 150
#define MAX_FLIGHTS 350

typedef struct {
    int to, cost;
} Edge;

int D, P, C, F, S;
int dist[MAX_CITIES];
Edge paths[MAX_PATHS];
Edge flights[MAX_FLIGHTS];

void bellman_ford() {
    for (int i = 1; i <= C; i++) {
        dist[i] = INT_MIN;
    }
    dist[S] = D;

    for (int i = 1; i < C; i++) {
        for (int j = 0; j < P; j++) {
            int u = paths[j].to;
            int v = paths[j].cost;
            if (dist[u] != INT_MIN && dist[u] + D > dist[v]) {
                dist[v] = dist[u] + D;
            }
        }
        for (int j = 0; j < F; j++) {
            int u = flights[j].to;
            int v = flights[j].cost;
            int cost = flights[j].cost;
            if (dist[u] != INT_MIN && dist[u] - cost + D > dist[v]) {
                dist[v] = dist[u] - cost + D;
            }
        }
    }

    for (int j = 0; j < P; j++) {
        int u = paths[j].to;
        int v = paths[j].cost;
        if (dist[u] != INT_MIN && dist[u] + D > dist[v]) {
            printf("-1\n");
            return;
        }
    }
    for (int j = 0; j < F; j++) {
        int u = flights[j].to;
        int v = flights[j].cost;
        int cost = flights[j].cost;
        if (dist[u] != INT_MIN && dist[u] - cost + D > dist[v]) {
            printf("-1\n");
            return;
        }
    }

    int max_money = 0;
    for (int i = 1; i <= C; i++) {
        if (dist[i] > max_money) {
            max_money = dist[i];
        }
    }
    printf("%d\n", max_money);
}

int main() {
    scanf("%d %d %d %d %d", &D, &P, &C, &F, &S);
    for (int i = 0; i < P; i++) {
        scanf("%d %d", &paths[i].to, &paths[i].cost);
    }
    for (int i = 0; i < F; i++) {
        scanf("%d %d %d", &flights[i].to, &flights[i].cost, &flights[i].cost);
    }
    bellman_ford();
    return 0;
}