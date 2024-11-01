#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 50005
#define MAXM 500005

typedef long long ll;

struct Edge {
    int to, next;
    ll cost;
} edges[MAXM * 2];

int head[MAXN], edgeCount;

void addEdge(int from, int to, ll cost) {
    edges[edgeCount].to = to;
    edges[edgeCount].cost = cost;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

ll dist[MAXN];
int parent[MAXN];

void dijkstra(int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = LLONG_MAX;
    }
    dist[1] = 0;
    parent[1] = -1;

    for (int i = 1; i < n; i++) {
        int u = -1;
        for (int j = 1; j <= n; j++) {
            if (u == -1 || dist[j] < dist[u]) {
                u = j;
            }
        }
        for (int j = head[u]; j != -1; j = edges[j].next) {
            int v = edges[j].to;
            ll weight = edges[j].cost;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int v[MAXN];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &v[i]);
    }

    memset(head, -1, sizeof(head));
    edgeCount = 0;

    for (int i = 0; i < m; i++) {
        int sl, sr, tl, tr, w;
        scanf("%d %d %d %d %d", &sl, &sr, &tl, &tr, &w);
        for (int j = sl; j <= sr; j++) {
            for (int k = tl; k <= tr; k++) {
                addEdge(j, k, (ll)w);
            }
        }
    }

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (v[i] > 0 && v[j] > 0) {
                addEdge(i, j, (ll)abs(i - j) * (ll)v[i]);
            }
        }
    }

    dijkstra(n);

    if (dist[n] == LLONG_MAX) {
        printf("-1\n");
    } else {
        printf("%lld\n", dist[n]);
        if (parent[n] == -1) {
            printf("0\n");
        } else {
            int count = 0;
            int path[MAXN];
            int u = n;
            while (u != -1) {
                path[count++] = u;
                u = parent[u];
            }
            printf("%d\n", count);
            for (int i = count - 1; i >= 0; i--) {
                printf("%d ", path[i]);
            }
            printf("\n");
        }
    }

    return 0;
}