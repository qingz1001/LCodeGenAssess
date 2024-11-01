#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100

int min(int a, int b) {
    return (a < b) ? a : b;
}

void floydWarshall(int dist[MAX_N][MAX_N], int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    int n, p;
    scanf("%d", &n);
    int dist[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &dist[i][j]);
        }
    }
    floydWarshall(dist, n);
    scanf("%d", &p);
    int treasure[MAX_N];
    for (int i = 0; i < p; i++) {
        scanf("%d", &treasure[i]);
    }

    int result = 0;
    int start = 0;
    for (int i = 0; i < p; i++) {
        result += dist[start][treasure[i]-1];
        start = treasure[i]-1;
    }
    result += dist[start][n-1];

    printf("%d\n", result);

    return 0;
}