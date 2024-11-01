#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_E 500000
#define MAX_Q 300000

int parent[MAX_N + 1];
int rank[MAX_N + 1];

void init(int n) {
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

void union_sets(int x, int y) {
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

int main() {
    int N, E, Q;
    scanf("%d %d", &N, &E);
    init(N);

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(u, v);
    }

    scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int type, A, B, G1 = -1, G2 = -1, C = -1;
        scanf("%d", &type);
        if (type == 1) {
            scanf("%d %d %d %d", &A, &B, &G1, &G2);
        } else if (type == 2) {
            scanf("%d %d %d", &A, &B, &C);
        }

        if (type == 1) {
            int originalRootA = find(A);
            int originalRootB = find(B);
            int originalRootG1 = find(G1);
            int originalRootG2 = find(G2);

            // Block the road between G1 and G2
            union_sets(G1, G2);

            int newRootA = find(A);
            int newRootB = find(B);

            // Restore the road between G1 and G2
            union_sets(G1, G2);

            if (originalRootA == originalRootB && newRootA != newRootB) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        } else if (type == 2) {
            int originalRootA = find(A);
            int originalRootB = find(B);
            int originalRootC = find(C);

            // Cut off city C
            for (int j = 1; j <= N; j++) {
                if (j != C) {
                    union_sets(j, C);
                }
            }

            int newRootA = find(A);
            int newRootB = find(B);

            // Restore city C
            for (int j = 1; j <= N; j++) {
                if (j != C) {
                    union_sets(j, C);
                }
            }

            if (originalRootA == originalRootB && newRootA != newRootB) {
                printf("yes\n");
            } else {
                printf("no\n");
            }
        }
    }

    return 0;
}