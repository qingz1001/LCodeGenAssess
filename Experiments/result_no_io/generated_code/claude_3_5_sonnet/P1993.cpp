#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 5005
#define INF 1000000000

int n, m;
long long d[MAXN];
bool vis[MAXN];

struct Edge {
    int to, w;
    struct Edge* next;
} *adj[MAXN];

void addEdge(int u, int v, int w) {
    struct Edge* e = (struct Edge*)malloc(sizeof(struct Edge));
    e->to = v;
    e->w = w;
    e->next = adj[u];
    adj[u] = e;
}

bool spfa(int s) {
    for (int i = 1; i <= n; i++) {
        d[i] = INF;
        vis[i] = false;
    }
    d[s] = 0;
    vis[s] = true;

    int q[MAXN], front = 0, rear = 0;
    q[rear++] = s;

    while (front != rear) {
        int u = q[front++];
        if (front == MAXN) front = 0;
        vis[u] = false;

        for (struct Edge* e = adj[u]; e; e = e->next) {
            int v = e->to, w = e->w;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                if (!vis[v]) {
                    vis[v] = true;
                    q[rear++] = v;
                    if (rear == MAXN) rear = 0;
                    if (rear == front) return false;  // 存在负环
                }
            }
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);

    for (int i = 0; i < m; i++) {
        int type, a, b, c;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d%d%d", &a, &b, &c);
            addEdge(b, a, c);
        } else if (type == 2) {
            scanf("%d%d%d", &a, &b, &c);
            addEdge(a, b, -c);
        } else {
            scanf("%d%d", &a, &b);
            addEdge(a, b, 0);
            addEdge(b, a, 0);
        }
    }

    for (int i = 1; i <= n; i++) {
        addEdge(0, i, 0);
    }

    if (spfa(0)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}