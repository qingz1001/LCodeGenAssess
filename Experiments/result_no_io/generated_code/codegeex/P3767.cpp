#include <stdio.h>
#include <stdlib.h>

#define MAXN 100000
#define MAXM 100000

typedef struct {
    int u;
    int v;
    int type;
} Operation;

typedef struct {
    int color;
    int parent;
    int rank;
} UnionFindSet;

Operation operations[MAXM];
UnionFindSet ufsets[MAXN + 1];

void initializeUnionFindSet(int n) {
    for (int i = 1; i <= n; i++) {
        ufsets[i].color = 0;
        ufsets[i].parent = i;
        ufsets[i].rank = 0;
    }
}

int find(int x) {
    if (ufsets[x].parent != x) {
        ufsets[x].parent = find(ufsets[x].parent);
    }
    return ufsets[x].parent;
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (ufsets[rootX].rank > ufsets[rootY].rank) {
            ufsets[rootY].parent = rootX;
        } else if (ufsets[rootX].rank < ufsets[rootY].rank) {
            ufsets[rootX].parent = rootY;
        } else {
            ufsets[rootY].parent = rootX;
            ufsets[rootX].rank++;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &operations[i].type, &operations[i].u);
        if (operations[i].type == 1 || operations[i].type == 2) {
            scanf("%d", &operations[i].v);
        }
    }

    initializeUnionFindSet(N);

    for (int i = 0; i < M; i++) {
        int k = operations[i].u;
        while (k != 0) {
            // Reverse the operation
            if (operations[k - 1].type == 1) {
                unionSets(operations[k - 1].u, operations[k - 1].v);
            } else if (operations[k - 1].type == 2) {
                unionSets(operations[k - 1].u, operations[k - 1].v);
            }
            k = operations[k - 1].u;
        }

        if (operations[i].type == 1) {
            unionSets(operations[i].u, operations[i].v);
        } else if (operations[i].type == 2) {
            unionSets(operations[i].u, operations[i].v);
        } else if (operations[i].type == 3) {
            // Reverse the deletion
            if (operations[operations[i].v - 1].type == 1) {
                unionSets(operations[operations[i].v - 1].u, operations[operations[i].v - 1].v);
            } else if (operations[operations[i].v - 1].type == 2) {
                unionSets(operations[operations[i].v - 1].u, operations[operations[i].v - 1].v);
            }
        }

        // Check if all nodes are connected
        int root = find(1);
        int allConnected = 1;
        for (int j = 2; j <= N; j++) {
            if (find(j) != root) {
                allConnected = 0;
                break;
            }
        }

        if (allConnected) {
            printf("excited\n");
        } else {
            printf("naive\n");
        }
    }

    return 0;
}