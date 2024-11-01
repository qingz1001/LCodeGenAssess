#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_N 51
#define MAX_M 1001
#define INF 1e9

int N, M, Q;
double graph[MAX_N][MAX_N];
double dist[MAX_N];
int visited[MAX_N];

void init_graph() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph[i][j] = INF;
        }
    }
}

int check(double mid) {
    for (int i = 1; i <= N; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[1] = 0;

    for (int i = 1; i <= N; i++) {
        int u = -1;
        for (int j = 1; j <= N; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == INF) break;
        visited[u] = 1;

        for (int v = 1; v <= N; v++) {
            if (graph[u][v] != INF) {
                double newDist = dist[u] + graph[u][v] - mid;
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                }
            }
        }
    }

    return dist[N] <= 0;
}

double binary_search() {
    double left = 0, right = INF;
    while (right - left > 1e-4) {
        double mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return left;
}

int main() {
    scanf("%d %d", &N, &M);
    init_graph();

    for (int i = 0; i < M; i++) {
        int A, B, W;
        scanf("%d %d %d", &A, &B, &W);
        graph[A][B] = W;
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int X, Y;
        scanf("%d %d", &X, &Y);

        // 交换起点和终点
        for (int j = 1; j <= N; j++) {
            double temp = graph[1][j];
            graph[1][j] = graph[X][j];
            graph[X][j] = temp;
        }
        for (int j = 1; j <= N; j++) {
            double temp = graph[j][N];
            graph[j][N] = graph[j][Y];
            graph[j][Y] = temp;
        }

        double result = binary_search();
        if (result >= INF - 1) {
            printf("OMG!\n");
        } else {
            printf("%.3f\n", result);
        }

        // 恢复图
        for (int j = 1; j <= N; j++) {
            double temp = graph[1][j];
            graph[1][j] = graph[X][j];
            graph[X][j] = temp;
        }
        for (int j = 1; j <= N; j++) {
            double temp = graph[j][N];
            graph[j][N] = graph[j][Y];
            graph[j][Y] = temp;
        }
    }

    return 0;
}