#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 50005
#define MAX_M 50005

typedef long long ll;

int n, m;
ll v[MAX_N];
ll dist[MAX_N];
int prev[MAX_N];

struct Tunnel {
    int sl, sr, tl, tr;
    ll w;
} tunnels[MAX_M];

void dijkstra() {
    int visited[MAX_N] = {0};
    for (int i = 2; i <= n; i++) {
        dist[i] = LLONG_MAX;
    }
    dist[1] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1;
        ll min_dist = LLONG_MAX;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                u = j;
                min_dist = dist[j];
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        // Check tunnels
        for (int j = 0; j < m; j++) {
            if (u >= tunnels[j].sl && u <= tunnels[j].sr) {
                for (int k = tunnels[j].tl; k <= tunnels[j].tr; k++) {
                    if (dist[u] + tunnels[j].w < dist[k]) {
                        dist[k] = dist[u] + tunnels[j].w;
                        prev[k] = u;
                    }
                }
            }
        }

        // Check digging
        if (v[u] > 0) {
            for (int j = 1; j <= n; j++) {
                ll new_dist = dist[u] + (ll)abs(u - j) * v[u];
                if (new_dist < dist[j]) {
                    dist[j] = new_dist;
                    prev[j] = u;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &v[i]);
    }
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d %d %lld", &tunnels[i].sl, &tunnels[i].sr, &tunnels[i].tl, &tunnels[i].tr, &tunnels[i].w);
    }

    dijkstra();

    if (dist[n] == LLONG_MAX) {
        printf("-1\n");
    } else {
        printf("%lld\n", dist[n]);
        int path[MAX_N], path_len = 0;
        for (int i = n; i != 0; i = prev[i]) {
            path[path_len++] = i;
        }
        printf("%d\n", path_len);
        for (int i = path_len - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\n");
    }

    return 0;
}