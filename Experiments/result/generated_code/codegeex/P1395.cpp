#include <stdio.h>
#include <stdlib.h>

#define MAXN 50001

int n;
int parent[MAXN], size[MAXN], depth[MAXN];

struct Edge {
    int to;
    struct Edge* next;
} *head[MAXN], *tail[MAXN];

int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }
}

void dfs(int u, int p) {
    depth[u] = depth[p] + 1;
    for (struct Edge* e = head[u]; e; e = e->next) {
        int v = e->to;
        if (v == p) continue;
        dfs(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        struct Edge* newEdge1 = (struct Edge*)malloc(sizeof(struct Edge));
        newEdge1->to = b;
        newEdge1->next = head[a];
        head[a] = newEdge1;

        struct Edge* newEdge2 = (struct Edge*)malloc(sizeof(struct Edge));
        newEdge2->to = a;
        newEdge2->next = head[b];
        head[b] = newEdge2;
    }

    int root = 1;
    for (int i = 2; i <= n; i++) {
        if (find(i) != find(root)) {
            unite(i, root);
            root = find(i);
        }
    }

    dfs(root, 0);

    int meetingPoint = root;
    int minDistanceSum = 0;
    for (int i = 1; i <= n; i++) {
        minDistanceSum += depth[i];
    }

    printf("%d %d\n", meetingPoint, minDistanceSum);

    return 0;
}