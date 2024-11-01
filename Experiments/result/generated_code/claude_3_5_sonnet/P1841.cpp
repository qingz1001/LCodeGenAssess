#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 201
#define MAX_M 20000
#define INF 1000000000

int n, m;
int graph[MAX_N][MAX_N];
int dist[MAX_N][MAX_N];
int important[MAX_N];

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                graph[i][j] = dist[i][j] = 0;
            } else {
                graph[i][j] = dist[i][j] = INF;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        graph[a][b] = graph[b][a] = c;
        dist[a][b] = dist[b][a] = c;
    }

    floyd();

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            for (int j = i + 1; j <= n; j++) {
                if (i != k && j != k) {
                    int new_dist = INF;
                    for (int p = 1; p <= n; p++) {
                        if (p != k) {
                            new_dist = (new_dist < dist[i][p] + dist[p][j]) ? new_dist : dist[i][p] + dist[p][j];
                        }
                    }
                    if (new_dist > dist[i][j]) {
                        important[k] = 1;
                        break;
                    }
                }
            }
            if (important[k]) break;
        }
    }

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (important[i]) {
            if (count > 0) printf(" ");
            printf("%d", i);
            count++;
        }
    }

    if (count == 0) {
        printf("No important cities.\n");
    } else {
        printf("\n");
    }

    return 0;
}