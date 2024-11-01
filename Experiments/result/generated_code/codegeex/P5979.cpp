#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000005
#define MOD 1000000007

int n;
int c[MAXN], d[MAXN];
int dp[MAXN], f[MAXN], g[MAXN], h[MAXN], pre[MAXN], suf[MAXN], q[MAXN], hd, tl;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &c[i], &d[i]);
    }

    // 初始化dp数组，f数组，g数组，h数组
    memset(dp, 0, sizeof(dp));
    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(h, 0, sizeof(h));
    memset(pre, 0, sizeof(pre));
    memset(suf, 0, sizeof(suf));
    hd = 1;
    tl = 0;
    q[0] = 0;

    // 动态规划求解
    for (int i = 1; i <= n; i++) {
        // 维护单调队列，找到满足条件的最大区间
        while (hd <= tl && i - q[hd] > d[q[hd]]) hd++;
        while (hd <= tl && c[q[tl]] > c[i]) tl--;
        q[++tl] = i;

        // 更新dp数组
        dp[i] = dp[q[hd]] + 1;
        f[i] = (f[q[hd]] + pre[i - 1] - pre[q[hd]]) % MOD;
        g[i] = (g[q[hd]] + suf[q[hd]] - suf[i - 1]) % MOD;
        h[i] = (h[q[hd]] + suf[i - 1] - suf[q[hd]]) % MOD;

        // 更新前缀和后缀数组
        pre[i] = (pre[i - 1] + f[i]) % MOD;
        suf[i] = (suf[i - 1] + g[i]) % MOD;
    }

    // 输出结果
    if (dp[n] == 0) {
        printf("NIE\n");
    } else {
        printf("%d %d\n", dp[n], (f[n] + g[n] + h[n]) % MOD);
    }

    return 0;
}