#include <stdio.h>
#include <stdlib.h>

#define MAXN 1001
#define MAXM 10001

int parent[MAXN];
int rank[MAXN];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findSet(int x) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);

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

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    int edges[MAXM][3];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
        edges[i][0]--;
        edges[i][1]--;
    }

    makeSet(N);

    int result = 0;
    int edgesUsed = 0;
    int components = N;

    // Kruskal's algorithm
    for (int i = 0; i < M && components > K; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int cost = edges[i][2];

        if (findSet(u) != findSet(v)) {
            unionSet(u, v);
            result += cost;
            edgesUsed++;
            components--;
        }
    }

    if (components > K) {
        printf("No Answer\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}