#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAXN 5005
#define INF INT_MAX / 2

int dist[MAXN];
bool visited[MAXN];
int n, m;

struct Edge {
    int to, weight;
    struct Edge* next;
} *adj[MAXN];

void addEdge(int from, int to, int weight) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = to;
    e->weight = weight;
    e->next = adj[from];
    adj[from] = e;
}

bool bellmanFord() {
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;

    for (int i = 0; i <= n; i++) {
        bool updated = false;
        for (int u = 0; u <= n; u++) {
            if (dist[u] == INF) continue;
            for (struct Edge* e = adj[u]; e; e = e->next) {
                int v = e->to, w = e->weight;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    updated = true;
                }
            }
        }
        if (!updated) return true;
    }
    return false;
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int type, a, b, c;
        scanf("%d", &type);
        if (type == 3) {
            scanf("%d%d", &a, &b);
            addEdge(a, b, 0);
            addEdge(b, a, 0);
        } else {
            scanf("%d%d%d", &a, &b, &c);
            if (type == 1) {
                addEdge(b, a, c);
            } else {
                addEdge(a, b, -c);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        addEdge(0, i, 0);
    }

    if (bellmanFord()) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}