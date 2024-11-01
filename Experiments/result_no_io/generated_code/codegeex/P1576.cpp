#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x3f3f3f3f

typedef struct {
    int u, v, w;
} Edge;

int n, m;
Edge edges[100010];
int head[2005], nxt[100010], tot;
double dist[2005];
bool inQueue[2005];

void addEdge(int u, int v, int w) {
    edges[tot].u = u;
    edges[tot].v = v;
    edges[tot].w = w;
    nxt[tot] = head[u];
    head[u] = tot++;
}

void SPFA(int start) {
    memset(dist, INF, sizeof(dist));
    memset(inQueue, false, sizeof(inQueue));
    dist[start] = 0;
    inQueue[start] = true;
    int u, v, w;
    for (int i = 0; i < n; i++) {
        u = start;
        for (int j = head[u]; j != -1; j = nxt[j]) {
            v = edges[j].v;
            w = edges[j].w;
            if (dist[u] + w / 100.0 < dist[v]) {
                dist[v] = dist[u] + w / 100.0;
                if (!inQueue[v]) {
                    inQueue[v] = true;
                    if (i == n - 1) {
                        printf("%.8lf\n", 100.0 / (1 - dist[v]));
                        exit(0);
                    }
                }
            }
        }
        inQueue[u] = false;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    memset(head, -1, sizeof(head));
    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
    int A, B;
    scanf("%d%d", &A, &B);
    SPFA(A);
    printf("%.8lf\n", 100.0 / (1 - dist[B]));
    return 0;
}