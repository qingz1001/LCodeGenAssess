#include <stdio.h>
#include <stdlib.h>

#define MAXN 55
#define INF 1000000000

int n, m, k;
int r[MAXN], d[MAXN];
int castle[MAXN];
int dist[MAXN];

void dijkstra(int start) {
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[start] = 0;
    int visited[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        visited[u] = 1;
        for (int v = 0; v < n; v++) {
            if (dist[v] > dist[u] + d[r[u]] * abs(u - v)) {
                dist[v] = dist[u] + d[r[u]] * abs(u - v);
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0; i < n; i++) scanf("%d", &r[i]);
    for (int i = 0; i < n; i++) scanf("%d", &d[i]);
    for (int i = 0; i < m; i++) scanf("%d", &castle[i]);

    int ans = INF;
    for (int i = 0; i < n; i++) {
        if (i >= m) continue;
        int max_dist = 0;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                dijkstra(j);
                int min_dist = INF;
                for (int c = 0; c < m; c++) {
                    if (castle[c] != i) {
                        min_dist = dist[castle[c]];
                        break;
                    }
                }
                if (min_dist < dist[j]) {
                    min_dist = dist[j];
                }
                if (min_dist > max_dist) {
                    max_dist = min_dist;
                }
            }
        }
        if (max_dist < ans) {
            ans = max_dist;
        }
    }

    printf("%d\n", ans);

    return 0;
}