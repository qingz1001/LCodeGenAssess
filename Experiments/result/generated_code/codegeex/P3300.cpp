#include <stdio.h>
#include <string.h>

int n, m, q;
char a[100005][7];
int b[100005][7], cnt[100005], c[100005][7];
int f[100005][7], fa[100005 * 6], size[100005 * 6];

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx != fy) {
        fa[fx] = fy;
        size[fy] += size[fx];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%s", a[i] + 1);
    }
    scanf("%d", &q);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            b[i][j] = (i - 1) * m + j;
            f[i][j] = b[i][j];
            cnt[i] += (a[i][j] == 'O');
        }
    }
    for (int i = 1; i <= n * m * 6; i++) {
        fa[i] = i;
        size[i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 'O') {
                if (a[i - 1][j] == 'O') {
                    merge(b[i][j], b[i - 1][j]);
                }
                if (a[i][j - 1] == 'O') {
                    merge(b[i][j], b[i][j - 1]);
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == '|') {
                merge(b[i][j], b[i - 1][j]);
            }
            if (a[i][j] == '-') {
                merge(b[i][j], b[i][j - 1]);
            }
            if (a[i][j] == '+') {
                merge(b[i][j], b[i - 1][j]);
                merge(b[i][j], b[i][j - 1]);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j] = find(b[i][j]);
        }
    }
    for (int i = 1; i <= q; i++) {
        char op;
        int x, y, k;
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'C') {
            scanf(" %c", &a[x][y]);
            cnt[x] -= (a[x][y] == 'O');
            for (int j = 1; j <= m; j++) {
                c[x][j] = find(b[x][j]);
            }
            for (int j = 1; j <= m; j++) {
                if (a[x][j] == 'O') {
                    if (a[x - 1][j] == 'O') {
                        merge(b[x][j], b[x - 1][j]);
                    }
                    if (a[x][j - 1] == 'O') {
                        merge(b[x][j], b[x][j - 1]);
                    }
                }
            }
            for (int j = 1; j <= m; j++) {
                c[x][j] = find(b[x][j]);
            }
        } else {
            int ans = 0;
            for (int j = 1; j <= y; j++) {
                ans += (c[x][j] == c[x - 1][j]);
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}