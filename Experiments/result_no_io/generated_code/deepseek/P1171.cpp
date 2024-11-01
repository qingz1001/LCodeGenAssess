#include <stdio.h>
#include <limits.h>

#define MAXN 20

int n;
int dist[MAXN][MAXN];
int min_cost = INT_MAX;
int visited[MAXN];

void tsp(int current, int count, int cost) {
    if (count == n && dist[current][0] > 0) {
        if (cost + dist[current][0] < min_cost) {
            min_cost = cost + dist[current][0];
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i] && dist[current][i] > 0) {
            visited[i] = 1;
            tsp(i, count + 1, cost + dist[current][i]);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }

    visited[0] = 1;
    tsp(0, 1, 0);

    printf("%d\n", min_cost);

    return 0;
}