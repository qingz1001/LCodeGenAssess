#include <stdio.h>
#include <stdlib.h>

#define MAXN 30005

typedef struct {
    int to;
    int next;
} Edge;

Edge edges[MAXN * 2];
int head[MAXN], edgeCount = 0;

void addEdge(int from, int to) {
    edges[edgeCount].to = to;
    edges[edgeCount].next = head[from];
    head[from] = edgeCount++;
}

int parent[MAXN], rank[MAXN];

void initUnionFind(int n) {
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

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

int maxWeight[MAXN];
int weightSum[MAXN];

void updateMax(int node, int newWeight) {
    while (node != -1) {
        maxWeight[node] = newWeight > maxWeight[node] ? newWeight : maxWeight[node];
        node = find(node);
    }
}

long long querySum(int node1, int node2) {
    long long sum = 0;
    while (find(node1) != find(node2)) {
        sum += weightSum[find(node1)];
        node1 = find(node1);
    }
    return sum + weightSum[find(node1)];
}

int main() {
    int n, q;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(a, b);
        addEdge(b, a);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &maxWeight[i]);
        weightSum[i] = maxWeight[i];
    }
    initUnionFind(n);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char operation[10];
        scanf("%s", operation);
        if (operation[0] == 'C') {
            int u, t;
            scanf("%d %d", &u, &t);
            updateMax(u, t);
            weightSum[u] = t;
        } else if (operation[0] == 'Q' && operation[1] == 'M') {
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%d\n", maxWeight[find(u)]);
        } else if (operation[0] == 'Q' && operation[1] == 'S') {
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%lld\n", querySum(u, v));
        }
    }
    return 0;
}