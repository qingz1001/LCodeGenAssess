#include <stdio.h>
#include <stdbool.h>

#define MAXN 1000
#define MAXM 1000
#define MAXQ 1000

int N, M, Q;
char canvas[MAXN][MAXM];
int parent[MAXN * MAXM];
int rank[MAXN * MAXM];
bool visited[MAXN][MAXM];

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

void dfs(int x, int y, int label) {
    if (x < 0 || x >= N || y < 0 || y >= M || visited[x][y] || canvas[x][y] != canvas[label / M][label % M]) {
        return;
    }
    visited[x][y] = true;
    union_sets(label, x * M + y);
    dfs(x - 1, y, label);
    dfs(x + 1, y, label);
    dfs(x, y - 1, label);
    dfs(x, y + 1, label);
}

int main() {
    scanf("%d %d %d", &N, &M, &Q);
    for (int i = 0; i < N; i++) {
        scanf("%s", canvas[i]);
    }

    for (int i = 0; i < N * M; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!visited[i][j]) {
                dfs(i, j, i * M + j);
            }
        }
    }

    for (int q = 0; q < Q; q++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        x1--; y1--; x2--; y2--;

        int count = 0;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j <= y2; j++) {
                if (find(i * M + j) == i * M + j) {
                    count++;
                }
            }
        }
        printf("%d\n", count);
    }

    return 0;
}