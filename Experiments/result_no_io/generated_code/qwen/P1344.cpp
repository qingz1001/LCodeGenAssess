#include <stdio.h>
#include <stdlib.h>

#define MAX_N 32
#define MAX_M 1000

typedef struct {
    int s, e, c;
} Edge;

int n, m;
Edge edges[MAX_M];
int dist[MAX_N][MAX_N];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] != -1 && dist[k][j] != -1) {
                    if (dist[i][j] == -1 || dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d %d %d", &edges[i].s, &edges[i].e, &edges[i].c);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = i == j ? 0 : -1;
        }
    }

    for (int i = 1; i <= m; i++) {
        dist[edges[i].s][edges[i].e] = edges[i].c;
    }

    floyd();

    int min_cost = 0, min_trucks = 0;
    for (int i = 1; i <= m; i++) {
        if (dist[1][n] == -1 || dist[1][edges[i].s] + edges[i].c + dist[edges[i].e][n] < dist[1][n]) {
            min_cost += edges[i].c;
            min_trucks++;
        }
    }

    printf("%d %d\n", min_cost, min_trucks);

    return 0;
}