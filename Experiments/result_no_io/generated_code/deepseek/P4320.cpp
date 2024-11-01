#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500005

typedef struct {
    int v, next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], eid;
int n, m, q;
int parent[MAXN], rank[MAXN];

void init() {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_set(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px != py) {
        if (rank[px] > rank[py]) {
            parent[py] = px;
        } else if (rank[px] < rank[py]) {
            parent[px] = py;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
}

void add_edge(int u, int v) {
    edges[eid].v = v;
    edges[eid].next = head[u];
    head[u] = eid++;
}

int bfs(int start, int end) {
    bool visited[MAXN] = {false};
    int queue[MAXN], front = 0, rear = 0;
    int count = 0;

    queue[rear++] = start;
    visited[start] = true;
    count++;

    while (front < rear) {
        int u = queue[front++];
        for (int i = head[u]; i != -1; i = edges[i].next) {
            int v = edges[i].v;
            if (!visited[v]) {
                visited[v] = true;
                queue[rear++] = v;
                count++;
                if (v == end) {
                    return count;
                }
            }
        }
    }
    return count;
}

int main() {
    scanf("%d %d", &n, &m);
    init();
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_set(u, v);
        add_edge(u, v);
        add_edge(v, u);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (find(u) != find(v)) {
            printf("0\n");
        } else {
            printf("%d\n", bfs(u, v));
        }
    }

    return 0;
}