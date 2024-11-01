#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_K 1000
#define MAX_H 500

int tree[MAX_N + 1][MAX_N + 1];
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
    if (rootX == rootY) return;
    if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

int main() {
    int n, k, h;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        tree[a][b] = 1;
        tree[b][a] = 1;
    }
    scanf("%d", &k);
    int positions[MAX_K + 1];
    for (int i = 1; i <= k; i++) {
        scanf("%d", &positions[i]);
    }
    scanf("%d", &h);
    int food_positions[MAX_H + 1];
    for (int i = 1; i <= h; i++) {
        scanf("%d", &food_positions[i]);
    }

    for (int t = 1; t <= h; t++) {
        init(n);
        for (int i = 1; i <= k; i++) {
            int pos = positions[i];
            while (pos != food_positions[t]) {
                int next_pos = -1;
                for (int j = 1; j <= n; j++) {
                    if (tree[pos][j] && !find(j)) {
                        next_pos = j;
                        break;
                    }
                }
                if (next_pos == -1) break;
                union_sets(pos, next_pos);
                pos = next_pos;
            }
            positions[i] = pos;
        }
    }

    for (int i = 1; i <= k; i++) {
        printf("%d %d\n", positions[i], t);
    }

    return 0;
}