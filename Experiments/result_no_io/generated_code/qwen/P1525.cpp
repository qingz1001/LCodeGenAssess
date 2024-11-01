#include <stdio.h>
#include <stdlib.h>

#define MAXN 20000
#define MAXM 100000

int N, M;
int edges[MAXM][3];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int compare(const void *a, const void *b) {
    return ((int *)b)[2] - ((int *)a)[2];
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }

    for (int i = 0; i <= N; i++) {
        parent[i] = i;
    }

    qsort(edges, M, sizeof(edges[0]), compare);

    long long min_conflict = 0;
    for (int i = 0; i < M; i++) {
        int a = edges[i][0] - 1;
        int b = edges[i][1] - 1;
        int c = edges[i][2];

        if (find(a) != find(b)) {
            union_sets(a, b);
        } else {
            min_conflict += c;
        }
    }

    printf("%lld\n", min_conflict);
    return 0;
}