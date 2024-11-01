#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define N 100010
int n, head[N], to[N << 1], nxt[N << 1], tot, w[N], c[N], f[N], ans[N];

void add(int x, int y) {
    to[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}

void dfs(int x) {
    for (int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        dfs(y);
        if (w[x] + w[y] <= c[x]) {
            f[x] = max(f[x], f[y] + 1);
        }
    }
    ans[x] = max(ans[x], f[x]);
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        scanf("%d", &f[i]);
        add(f[i], i);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    for (int i = 1; i <= n; i++) {
        dfs(i);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    return 0;
}