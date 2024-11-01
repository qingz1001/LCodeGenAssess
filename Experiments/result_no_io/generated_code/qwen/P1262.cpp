#include <stdio.h>
#include <stdlib.h>

#define MAX_SPY 3001
#define MAX_COST 20001

int parent[MAX_SPY];
int rank[MAX_SPY];

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

void union_set(int x, int y) {
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
    int n, p, r;
    scanf("%d", &n);
    scanf("%d", &p);

    int spies[MAX_SPY][2];
    for (int i = 0; i < p; i++) {
        scanf("%d %d", &spies[i][0], &spies[i][1]);
    }

    scanf("%d", &r);
    int edges[r * 2];
    for (int i = 0; i < r; i++) {
        scanf("%d %d", &edges[i * 2], &edges[i * 2 + 1]);
    }

    init(n);

    int total_cost = 0;
    int num_edges = 0;

    for (int i = 0; i < p; i++) {
        int spy = spies[i][0];
        int cost = spies[i][1];
        int root_spy = find(spy);
        if (root_spy == spy) {
            continue;
        }
        union_set(root_spy, spy);
        total_cost += cost;
        num_edges++;
        if (num_edges == n - 1) {
            break;
        }
    }

    for (int i = 0; i < r; i++) {
        int u = edges[i * 2];
        int v = edges[i * 2 + 1];
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            union_set(root_u, root_v);
            num_edges++;
        }
    }

    if (num_edges == n - 1) {
        printf("YES\n%d\n", total_cost);
    } else {
        int min_uncontrolled = n + 1;
        for (int i = 1; i <= n; i++) {
            if (find(i) == i) {
                min_uncontrolled = i;
                break;
            }
        }
        printf("NO\n%d\n", min_uncontrolled);
    }

    return 0;
}