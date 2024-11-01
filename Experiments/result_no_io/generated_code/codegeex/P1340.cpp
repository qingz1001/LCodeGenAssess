#include <stdio.h>
#include <stdlib.h>

#define MAXN 201
#define MAXW 6001

int parent[MAXN];

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
        parent[rootX] = rootY;
    }
}

int main() {
    int N, W;
    scanf("%d %d", &N, &W);

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
    }

    int totalWeight = 0;
    int edgeCount = 0;
    int edges[MAXW][3];
    int mstWeight[MAXW];
    int mstEdgeCount[MAXW];

    for (int i = 0; i < W; i++) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);

        // Initialize the union-find structure
        for (int j = 1; j <= N; j++) {
            parent[j] = j;
        }

        int k = 0;
        totalWeight = 0;
        edgeCount = 0;

        // Process all edges up to the current week
        for (int j = 0; j <= i; j++) {
            int rootX = find(edges[j][0]);
            int rootY = find(edges[j][1]);

            if (rootX != rootY) {
                unionSets(rootX, rootY);
                totalWeight += edges[j][2];
                edgeCount++;
                k++;
            }
        }

        if (edgeCount < N - 1) {
            printf("-1\n");
        } else {
            printf("%d\n", totalWeight);
            mstWeight[i] = totalWeight;
            mstEdgeCount[i] = edgeCount;
        }
    }

    return 0;
}