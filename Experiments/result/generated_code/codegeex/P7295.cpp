#include <stdio.h>
#include <string.h>

int n, m, q;
char grid[1001][1001];
int color[1001][1001];
int fa[1000001];
int size[1000001];
int count;

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void union_sets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        if (size[rootX] < size[rootY]) {
            fa[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            fa[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        count--;
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%s", grid[i] + 1);
    }

    // Initialize the color grid and union-find structures
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            color[i][j] = (i - 1) * m + j;
            fa[color[i][j]] = color[i][j];
            size[color[i][j]] = 1;
        }
    }

    // Union adjacent cells of the same color
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (i > 1 && grid[i][j] == grid[i - 1][j]) {
                union_sets(color[i][j], color[i - 1][j]);
            }
            if (j > 1 && grid[i][j] == grid[i][j - 1]) {
                union_sets(color[i][j], color[i][j - 1]);
            }
        }
    }

    // Process each query
    for (int i = 0; i < q; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        count = n * m;

        // Initialize the union-find structures for the query
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                fa[color[j][k]] = color[j][k];
                size[color[j][k]] = 1;
            }
        }

        // Union adjacent cells of the same color within the query rectangle
        for (int j = x1; j <= x2; j++) {
            for (int k = y1; k <= y2; k++) {
                if (j > x1 && grid[j][k] == grid[j - 1][k]) {
                    union_sets(color[j][k], color[j - 1][k]);
                }
                if (k > y1 && grid[j][k] == grid[j][k - 1]) {
                    union_sets(color[j][k], color[j][k - 1]);
                }
            }
        }

        // Count the number of disjoint sets
        int disjoint_sets = 0;
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                if (fa[color[j][k]] == color[j][k]) {
                    disjoint_sets++;
                }
            }
        }

        printf("%d\n", disjoint_sets);
    }

    return 0;
}