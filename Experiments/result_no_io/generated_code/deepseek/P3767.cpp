#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 100005
#define MAXM 100005

typedef struct {
    int type; // 1: u生v, 2: u克v, 3: 删除
    int u, v;
} Operation;

Operation operations[MAXM];
int parent[MAXN], rank[MAXN];
int n, m;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        if (rank[x] > rank[y]) {
            parent[y] = x;
        } else if (rank[x] < rank[y]) {
            parent[x] = y;
        } else {
            parent[y] = x;
            rank[x]++;
        }
    }
}

bool is_valid(int u, int v, int type) {
    int root_u = find(u);
    int root_v = find(v);
    if (type == 1) {
        // u生v
        if (root_u == root_v) return false;
        union_sets(u, v);
    } else if (type == 2) {
        // u克v
        if (root_u == root_v) return false;
        union_sets(u, v + n);
        union_sets(u + n, v);
    }
    return true;
}

void rollback(int u, int v, int type) {
    if (type == 1) {
        // 撤销u生v
        parent[u] = u;
        parent[v] = v;
    } else if (type == 2) {
        // 撤销u克v
        parent[u] = u;
        parent[v] = v;
        parent[u + n] = u + n;
        parent[v + n] = v + n;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        parent[i + n] = i + n;
        rank[i] = 0;
        rank[i + n] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int k, t;
        scanf("%d %d", &k, &t);
        if (t == 1 || t == 2) {
            int u, v;
            scanf("%d %d", &u, &v);
            operations[i].type = t;
            operations[i].u = u;
            operations[i].v = v;
        } else if (t == 3) {
            int x;
            scanf("%d", &x);
            operations[i].type = t;
            operations[i].u = x;
        }
    }

    for (int i = 1; i <= m; i++) {
        int k = operations[i].type == 3 ? operations[i].u : 0;
        if (k > 0) {
            // 回滚到第k次操作后的状态
            for (int j = k + 1; j < i; j++) {
                if (operations[j].type == 1 || operations[j].type == 2) {
                    rollback(operations[j].u, operations[j].v, operations[j].type);
                }
            }
        }

        if (operations[i].type == 1 || operations[i].type == 2) {
            int u = operations[i].u;
            int v = operations[i].v;
            if (!is_valid(u, v, operations[i].type)) {
                printf("naive\n");
                continue;
            }
        } else if (operations[i].type == 3) {
            int x = operations[i].u;
            rollback(operations[x].u, operations[x].v, operations[x].type);
        }

        printf("excited\n");
    }

    return 0;
}