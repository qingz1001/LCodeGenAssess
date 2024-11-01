#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1005
#define MAXP 10005

typedef struct {
    int to, len;
} Edge;

Edge edges[MAXP];
int adj[MAXN][MAXN];
int dist[MAXN];
int visited[MAXN];
int n, p, k;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int dijkstra(int max_cost) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (int j = 1; j <= n; j++) {
            if (adj[u][j] != -1) {
                int cost = adj[u][j] > max_cost ? 1 : 0;
                dist[j] = min(dist[j], dist[u] + cost);
            }
        }
    }

    return dist[n];
}

int main() {
    scanf("%d %d %d", &n, &p, &k);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            adj[i][j] = -1;
        }
    }

    for (int i = 0; i < p; i++) {
        int a, b, l;
        scanf("%d %d %d", &a, &b, &l);
        adj[a][b] = l;
        adj[b][a] = l;
    }

    int left = 0, right = 1000000, ans = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (dijkstra(mid) <= k) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    printf("%d\n", ans);

    return 0;
}