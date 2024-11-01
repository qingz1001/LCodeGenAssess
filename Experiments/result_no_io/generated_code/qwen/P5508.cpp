#include <stdio.h>
#include <stdlib.h>

#define MAXN 50005
#define INF 1e18

typedef long long ll;

int n, m;
ll v[MAXN];
int s[MAXN], t[MAXN], w[MAXN];

void dijkstra(int start) {
    ll dist[MAXN];
    for (int i = 1; i <= n; ++i) {
        dist[i] = INF;
    }
    dist[start] = 0;
    for (int k = 1; k <= n; ++k) {
        int u = -1;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] != INF && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }
        if (dist[u] == INF) break;
        for (int i = 1; i <= n; ++i) {
            if (v[i] > 0 && dist[i] > dist[u] + abs(i - u) * v[i]) {
                dist[i] = dist[u] + abs(i - u) * v[i];
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &v[i]);
    }
    for (int i = 1; i <= m; ++i) {
        scanf("%d %d %d %d %lld", &s[i], &t[i], &s[i], &t[i], &w[i]);
    }

    // Preprocess the tunnels
    for (int i = 1; i <= m; ++i) {
        for (int j = s[i]; j <= t[i]; ++j) {
            for (int k = s[i]; k <= t[i]; ++k) {
                // Add the tunnel between j and k with weight w[i]
                // This is a placeholder for actual graph construction logic
            }
        }
    }

    // Run Dijkstra's algorithm from the starting point (1)
    dijkstra(1);

    // Check if we can reach the nth cave
    if (dist[n] == INF) {
        printf("-1\n");
        return 0;
    }

    // Output the minimum time to reach the nth cave
    printf("%lld\n", dist[n]);

    // If no path is found, output 0
    if (dist[n] == INF) {
        printf("0\n");
        return 0;
    }

    // Otherwise, output the path
    printf("1\n");
    for (int i = 1; i <= n; ++i) {
        if (dist[i] != INF) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}