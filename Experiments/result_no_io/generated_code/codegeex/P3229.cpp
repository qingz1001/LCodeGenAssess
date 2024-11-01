#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 200005

int n, m, a[MAXN], b[MAXN], fa[MAXN], fb[MAXN], f[MAXN][2], g[MAXN][2], h[MAXN][2], x[MAXM], y[MAXM], z[MAXM], p[MAXM], q[MAXM], r[MAXM], s[MAXM], t[MAXM], u[MAXM], v[MAXM], w[MAXM], cnt[MAXM], len, pos;

int main() {
    int i, j, k, l, r, mid, ans = 0, sum = 0, top = 0;
    
    // 读取输入
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    
    // 初始化
    for (i = 1; i <= n; i++) {
        fa[i] = fb[i] = i;
        f[i][0] = g[i][0] = h[i][0] = i;
        f[i][1] = g[i][1] = h[i][1] = i - 1;
    }
    
    // 构建前缀和后缀
    for (i = 1; i <= n; i++) {
        k = a[i];
        l = b[i];
        while (k > fa[i]) {
            fa[i] = f[fa[k]][l];
            l = !l;
            k = a[f[k][l]];
        }
        while (k < fb[i]) {
            fb[i] = g[fb[k]][l];
            l = !l;
            k = a[g[k][l]];
        }
    }
    
    // 动态规划求解
    for (i = 1; i <= n; i++) {
        k = a[i];
        l = b[i];
        if (l) {
            f[k][l] = k;
            g[k][l] = k;
        } else {
            f[k][l] = h[k][1];
            g[k][l] = h[k][1];
        }
        h[k][l] = i;
    }
    
    // 构建字典序最小的方案
    for (i = 1; i < n; i++) {
        k = a[i];
        l = b[i];
        if (l) {
            x[i] = k;
            y[i] = k;
            z[i] = k;
        } else {
            x[i] = k;
            y[i] = fa[k];
            z[i] = fb[k];
        }
    }
    
    // 计算最优解
    for (i = 1; i < m; i++) {
        l = 0;
        for (j = 1; j < n; j++) {
            k = a[j];
            if (b[j]) {
                cnt[j] = 0;
            } else {
                cnt[j] = cnt[f[k][1]] + 1;
            }
            if (cnt[j] > l) {
                l = cnt[j];
                r = j;
            }
        }
        p[i] = r;
        q[i] = x[r];
        x[r] = y[r];
        y[r] = z[r];
        z[r] = 0;
        if (l > ans) {
            ans = l;
            pos = i;
        }
    }
    
    // 输出结果
    for (i = 1; i < pos; i++) {
        printf("%d ", q[i]);
    }
    printf("%d ", a[n]);
    for (i = pos; i < m; i++) {
        printf("%d ", q[i]);
    }
    
    return 0;
}