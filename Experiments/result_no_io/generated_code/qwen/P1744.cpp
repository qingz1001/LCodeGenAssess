#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 105
#define INF 1e9

int n, m;
double dist[MAXN][MAXN];
int graph[MAXN][MAXN];

void floydWarshall() {
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
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf %lf", &graph[i][1], &graph[i][2]);
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        double d = sqrt(pow(graph[u][1] - graph[v][1], 2) + pow(graph[u][2] - graph[v][2], 2));
        dist[u][v] = dist[v][u] = d;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (!graph[i][j] && !graph[j][i]) dist[i][j] = INF;
        }
    }
    floydWarshall();
    int s, t;
    scanf("%d %d", &s, &t);
    printf("%.2f\n", dist[s][t]);
    return 0;
}