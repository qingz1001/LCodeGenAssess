#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 150
#define MAXM 150
#define INF INT_MAX

typedef struct {
    int to, speed, length;
} Edge;

Edge graph[MAXN][MAXM];
int edge_count[MAXN];
double time_to[MAXN];
int prev[MAXN];
int visited[MAXN];

void dijkstra(int start, int n) {
    for (int i = 0; i < n; i++) {
        time_to[i] = INF;
        prev[i] = -1;
        visited[i] = 0;
    }
    time_to[start] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || time_to[j] < time_to[u])) {
                u = j;
            }
        }

        visited[u] = 1;
        for (int j = 0; j < edge_count[u]; j++) {
            int v = graph[u][j].to;
            int speed = graph[u][j].speed;
            int length = graph[u][j].length;
            double time = (speed == 0) ? length / 70.0 : length / (double)speed;
            if (time_to[u] + time < time_to[v]) {
                time_to[v] = time_to[u] + time;
                prev[v] = u;
            }
        }
    }
}

void print_path(int dest) {
    if (prev[dest] != -1) {
        print_path(prev[dest]);
    }
    printf("%d ", dest);
}

int main() {
    int N, M, D;
    scanf("%d %d %d", &N, &M, &D);

    for (int i = 0; i < N; i++) {
        edge_count[i] = 0;
    }

    for (int i = 0; i < M; i++) {
        int A, B, V, L;
        scanf("%d %d %d %d", &A, &B, &V, &L);
        graph[A][edge_count[A]].to = B;
        graph[A][edge_count[A]].speed = V;
        graph[A][edge_count[A]].length = L;
        edge_count[A]++;
    }

    dijkstra(0, N);

    print_path(D);
    printf("\n");

    return 0;
}