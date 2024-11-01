#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 201
#define MAXP 40001

struct Edge {
    int from;
    int to;
    int length;
};

int compare(const void *a, const void *b) {
    struct Edge *edgeA = (struct Edge *)a;
    struct Edge *edgeB = (struct Edge *)b;
    return edgeA->length - edgeB->length;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (xroot != yroot) {
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
}

int main() {
    int N, P, T;
    scanf("%d%d%d", &N, &P, &T);

    struct Edge edges[MAXP];
    for (int i = 0; i < P; i++) {
        scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].length);
    }

    qsort(edges, P, sizeof(struct Edge), compare);

    int parent[MAXN];
    int rank[MAXN];
    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int maxLen = 0;
    int edgesUsed = 0;
    int currentT = 0;

    while (currentT < T) {
        for (int i = 0; i < P && edgesUsed < N - 1; i++) {
            int from = edges[i].from;
            int to = edges[i].to;
            int length = edges[i].length;

            int x = find(parent, from);
            int y = find(parent, to);

            if (x != y) {
                unionSets(parent, rank, x, y);
                maxLen = length;
                edgesUsed++;
            }
        }

        if (edgesUsed == N - 1) {
            currentT++;
            edgesUsed = 0;
            for (int i = 1; i <= N; i++) {
                parent[i] = i;
                rank[i] = 0;
            }
        }
    }

    printf("%d\n", maxLen);
    return 0;
}