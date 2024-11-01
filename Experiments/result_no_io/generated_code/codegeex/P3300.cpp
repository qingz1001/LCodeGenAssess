#include <stdio.h>
#include <string.h>

#define N 100005
#define M 7

int n, m, q;
char grid[N][M];
int parent[N*M], size[N*M], count;

void make_set(int x) {
    parent[x] = x;
    size[x] = 1;
}

int find_set(int x) {
    if (parent[x] != x) {
        parent[x] = find_set(parent[x]);
    }
    return parent[x];
}

void union_sets(int x, int y) {
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (size[x] < size[y]) {
            int temp = x;
            x = y;
            y = temp;
        }
        parent[y] = x;
        size[x] += size[y];
        count--;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    scanf("%d", &q);

    count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') {
                make_set(i * m + j);
                count++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'O') {
                if (i > 0 && grid[i-1][j] == 'O') {
                    union_sets(i * m + j, (i-1) * m + j);
                }
                if (j > 0 && grid[i][j-1] == 'O') {
                    union_sets(i * m + j, i * m + j - 1);
                }
            }
        }
    }

    for (int i = 0; i < q; i++) {
        char op;
        int l, r;
        scanf(" %c %d %d", &op, &l, &r);
        if (op == 'C') {
            int x, y, k;
            scanf("%d", &k);
            x = l - 1;
            y = r - 1;
            if (grid[x][y] == 'O') {
                count--;
            }
            grid[x][y] = (char)k;
            if (grid[x][y] == 'O') {
                make_set(x * m + y);
                count++;
            }
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == 'O') {
                        union_sets(x * m + y, nx * m + ny);
                    }
                }
            }
        } else if (op == 'Q') {
            printf("%d\n", count);
        }
    }

    return 0;
}