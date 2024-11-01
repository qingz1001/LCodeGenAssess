#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 200
#define MAXM 10000
#define INF 1e9

typedef struct {
    int to, weight;
} Edge;

int n, m;
Edge edges[MAXM];
int dist[MAXN][MAXN];
int visited[MAXN];

void dijkstra(int start) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dist[i][j] = (i == j ? 0 : INF);
        }
    }

    for (int i = 0; i < m; ++i) {
        dist[edges[i].to - 1][edges[i].from - 1] = edges[i].weight;
        dist[edges[i].from - 1][edges[i].to - 1] = edges[i].weight;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = fmin(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
}

double findSecondShortestPath() {
    double firstShortest = INF, secondShortest = INF;
    for (int i = 0; i < n; ++i) {
        if (dist[0][i] < firstShortest) {
            secondShortest = firstShortest;
            firstShortest = dist[0][i];
        } else if (dist[0][i] < secondShortest && dist[0][i] != firstShortest) {
            secondShortest = dist[0][i];
        }
    }
    return secondShortest == INF ? -1 : secondShortest;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%*d %*d");
    }
    for (int i = 0; i < m; ++i) {
        scanf("%d %d", &edges[i].from, &edges[i].to);
        scanf("%d", &edges[i].weight);
    }

    dijkstra(0);
    double result = findSecondShortestPath();

    printf("%.2f\n", result);

    return 0;
}