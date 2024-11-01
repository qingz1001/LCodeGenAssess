#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 100005

typedef struct {
    int x, y, t;
} Edge;

int parent[MAXN];
int rank[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
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

int compare(const void *a, const void *b) {
    return ((Edge *)a)->t - ((Edge *)b)->t;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Edge edges[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i].x, &edges[i].y, &edges[i].t);
    }

    qsort(edges, M, sizeof(Edge), compare);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int earliestTime = -1;
    for (int i = 0; i < M; i++) {
        unionSet(edges[i].x, edges[i].y);
        int root = find(1);
        int connected = 1;
        for (int j = 2; j <= N; j++) {
            if (find(j) != root) {
                connected = 0;
                break;
            }
        }
        if (connected) {
            earliestTime = edges[i].t;
            break;
        }
    }

    printf("%d\n", earliestTime);

    return 0;
}