#include <stdio.h>
#include <string.h>

int n, G[2005][2005], vis[2005], ans[2005];
int cnt, col[2005], a[2005];

void dfs(int x, int c) {
    if (col[x]) {
        if (col[x] != c) {
            cnt = -1;
            return;
        }
        return;
    }
    col[x] = c;
    for (int i = 1; i <= n; i++) {
        if (G[x][i]) {
            dfs(i, c);
            if (cnt == -1) return;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        while (scanf("%d", &x) && x) {
            G[i][x] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!col[i]) {
            dfs(i, 1);
        }
        if (cnt == -1) break;
    }
    if (cnt == -1) {
        printf("No solution\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        a[col[i]]++;
    }

    int s = 0;
    for (int i = 1; i <= n; i++) {
        s += a[i];
    }
    int d = s / 2;

    int l = 0, r = s;
    for (int i = 1; i <= n; i++) {
        if (a[i] <= d) {
            l += a[i];
        } else {
            r -= a[i];
        }
    }

    if (l <= r) {
        printf("%d %d\n", l, r);
    } else {
        printf("%d %d\n", r, l);
    }

    return 0;
}