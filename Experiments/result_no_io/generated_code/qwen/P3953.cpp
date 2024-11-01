#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define INF 0x3f3f3f3f

typedef struct {
    int to, weight;
} Edge;

Edge edges[MAXN];
int graph[MAXN][MAXN];
int dist[MAXN], dp[MAXN];

void dijkstra(int n, int start) {
    memset(dist, INF, sizeof(dist));
    dist[start] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n * n; j++) {
            if (edges[j].weight != INF && dist[edges[j].from] != INF &&
                dist[edges[j].to] > dist[edges[j].from] + edges[j].weight) {
                dist[edges[j].to] = dist[edges[j].from] + edges[j].weight;
            }
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N, M, K, P;
        scanf("%d %d %d %d", &N, &M, &K, &P);

        for (int i = 0; i < N * N; i++) {
            edges[i].weight = INF;
        }

        for (int i = 0; i < M; i++) {
            int a, b, c;
            scanf("%d %d %d", &a, &b, &c);
            edges[i].from = a - 1;
            edges[i].to = b - 1;
            edges[i].weight = c;
        }

        dijkstra(N, 0);

        long long result = 0;
        for (int i = 0; i < N; i++) {
            if (dist[i] <= dist[N - 1] + K) {
                result++;
            }
        }

        if (result == 0) {
            printf("-1\n");
        } else {
            printf("%lld\n", result % P);
        }
    }
    return 0;
}