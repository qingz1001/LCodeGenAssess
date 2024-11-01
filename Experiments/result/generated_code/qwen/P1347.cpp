#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 27

int parent[MAX_N];
int rank[MAX_N];

void init(int n) {
    for (int i = 0; i <= n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void union_sets(int u, int v) {
    int pu = find(u);
    int pv = find(v);
    if (pu == pv) {
        return;
    }
    if (rank[pu] > rank[pv]) {
        parent[pv] = pu;
    } else if (rank[pu] < rank[pv]) {
        parent[pu] = pv;
    } else {
        parent[pv] = pu;
        rank[pu]++;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    init(n + 1);

    int relations[m][2];
    for (int i = 0; i < m; ++i) {
        char a, b;
        scanf(" %c <%c ", &a, &b);
        relations[i][0] = a - 'A' + 1;
        relations[i][1] = b - 'A' + 1;
        union_sets(relations[i][0], relations[i][1]);
    }

    int sorted = 1;
    for (int i = 1; i <= n; ++i) {
        if (find(i) != find(1)) {
            sorted = 0;
            break;
        }
    }

    if (!sorted) {
        printf("Sorted sequence cannot be determined.\n");
    } else {
        int count = 0;
        for (int i = 0; i < m; ++i) {
            if (find(relations[i][0]) != find(relations[i][1])) {
                union_sets(relations[i][0], relations[i][1]);
                count++;
            } else {
                printf("Inconsistency found after %d relations.\n", count + 1);
                return 0;
            }
        }
        printf("Sorted sequence determined after %d relations: A%s.\n", count, "BCDEFGHIJKLMNOPQRSTUVWXYZ" + (n - 1));
    }

    return 0;
}