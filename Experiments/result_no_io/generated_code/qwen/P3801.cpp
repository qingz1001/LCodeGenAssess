#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int n, m, q;
int grid[MAXN][MAXN];

void update(int x, int y) {
    for (int i = 0; i < n; ++i) {
        if (i != x - 1) {
            grid[i][y] ^= 1;
        }
    }
    for (int j = 0; j < m; ++j) {
        if (j != y - 1) {
            grid[x - 1][j] ^= 1;
        }
    }
}

int query(int x1, int y1, int x2, int y2) {
    int count = 0;
    for (int i = x1 - 1; i <= x2 - 1; ++i) {
        for (int j = y1 - 1; j <= y2 - 1; ++j) {
            count += grid[i][j];
        }
    }
    return count;
}

int main() {
    scanf("%d %d %d", &n, &m, &q);
    for (int i = 0; i < q; ++i) {
        int op, x, y, x1, y1, x2, y2;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            update(x, y);
        } else if (op == 2) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            printf("%d\n", query(x1, y1, x2, y2));
        }
    }
    return 0;
}