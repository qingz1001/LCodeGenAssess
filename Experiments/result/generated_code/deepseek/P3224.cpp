#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    int rank;
    int id;
} Island;

int n, m, q;
Island islands[MAXN];
int parent[MAXN];
int size[MAXN];
int rank_to_id[MAXN];

int cmp(const void *a, const void *b) {
    return ((Island *)a)->rank - ((Island *)b)->rank;
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
        if (size[rootX] < size[rootY]) {
            int temp = rootX;
            rootX = rootY;
            rootY = temp;
        }
        parent[rootY] = rootX;
        size[rootX] += size[rootY];
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &islands[i].rank);
        islands[i].id = i;
        parent[i] = i;
        size[i] = 1;
        rank_to_id[islands[i].rank] = i;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        union_sets(u, v);
    }

    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        char op;
        int x, y;
        scanf(" %c %d %d", &op, &x, &y);
        if (op == 'B') {
            union_sets(x, y);
        } else if (op == 'Q') {
            int rootX = find(x);
            if (size[rootX] < y) {
                printf("-1\n");
            } else {
                int count = 0;
                for (int j = 1; j <= n; j++) {
                    if (find(islands[j].id) == rootX) {
                        count++;
                        if (count == y) {
                            printf("%d\n", islands[j].id);
                            break;
                        }
                    }
                }
            }
        }
    }

    return 0;
}