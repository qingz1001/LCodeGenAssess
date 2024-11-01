#include <stdio.h>
#include <string.h>

int n, r[6005], f[6005][2], h[6005], e[6005], cnt, root;
struct edge {
    int to, next;
} a[6005];

void add(int x, int y) {
    a[++cnt].to = y;
    a[cnt].next = h[x];
    h[x] = cnt;
}

void dfs(int x) {
    f[x][1] = r[x];
    for (int i = h[x]; i; i = a[i].next) {
        int y = a[i].to;
        dfs(y);
        f[x][0] += f[y][1];
        f[x][1] += f[y][0];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &r[i]);
    }
    int x, y;
    while (scanf("%d%d", &x, &y) && x && y) {
        if (y == 0) {
            root = x;
        } else {
            add(y, x);
        }
    }
    dfs(root);
    printf("%d", f[root][1]);
    return 0;
}