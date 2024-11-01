#include <stdio.h>
#include <string.h>

int n, m, ans;
int f[101][21][21];

struct node {
    int l, r;
} a[201];

void dfs(int now, int sum1, int sum2) {
    if (now == n + 1) {
        ans = f[now][sum1][sum2] = (sum1 > 0 && sum1 * 5 + sum2 + 1 <= m) ? sum1 + sum2 : 0;
        return;
    }
    if (f[now][sum1][sum2] != -1) return;
    if (a[now].r == 0) {
        dfs(a[now].l, sum1, sum2);
        dfs(a[now].r, sum1, sum2);
    } else {
        dfs(a[now].l, sum1 + 1, sum2);
        dfs(a[now].r, sum1, sum2);
    }
    f[now][sum1][sum2] = ans;
}

int main() {
    scanf("%d", &m);
    m -= 1; // 逃跑时间
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].l, &a[i].r);
        if (a[i].r == 0) i++;
    }
    memset(f, -1, sizeof(f));
    dfs(1, 0, 0);
    printf("%d\n", f[1][0][0]);
    return 0;
}