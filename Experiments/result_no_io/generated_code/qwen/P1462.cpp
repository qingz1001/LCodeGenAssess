#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 500005

typedef struct {
    int to, next, weight;
} Edge;

Edge edges[MAXM];
int head[MAXN], edgeCount = 0;
int n, m, b;
int fees[MAXN];
int dist[MAXN][MAXN];

void addEdge(int from, int to, int weight) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    edges[edgeCount].weight = weight;
    head[from] = edgeCount++;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int bfs() {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dist[i][j] = INT_MAX / 2;
        }
    }
    dist[1][1] = 0;

    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (dist[k][i] == INT_MAX / 2) continue;
            for (int e = head[i]; e != -1; e = edges[e].next) {
                int j = edges[e].to;
                int w = edges[e].weight;
                if (dist[k][i] + w < dist[k][j]) {
                    dist[k][j] = dist[k][i] + w;
                }
            }
        }
    }

    int maxFee = 0;
    for (int i = 1; i <= n; ++i) {
        if (dist[n][i] <= b) {
            maxFee = max(maxFee, fees[i]);
        }
    }

    return maxFee == 0 ? -1 : maxFee;
}

int main() {
    scanf("%d %d %d", &n, &m, &b);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &fees[i]);
    }
    for (int i = 1; i <= n; ++i) {
        head[i] = -1;
    }

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    int result = bfs();
    if (result == -1) {
        printf("AFK\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}