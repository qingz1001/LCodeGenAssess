#include <stdio.h>
#include <string.h>

#define MAXN 30005

int n, q;
char s[MAXN];
int dp[MAXN][2];

void solve() {
    scanf("%d%d", &n, &q);
    scanf("%s", s + 1);

    // 预处理每个位置的最小代价
    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i-1][0] + 1; // 从左向右走
        dp[i][1] = dp[i+1][1] + 1; // 从右向左走
    }

    while (q--) {
        int i, p, k;
        scanf("%d%d%d", &i, &p, &k);

        int j = i;
        while (j <= n && s[i] == s[j]) j++; // 找到最远的j
        j--;

        int min_cost = dp[i][0] + n - j; // 不使用传送法阵的代价
        for (int l = i; l <= j; l++) {
            int r = l;
            while (r <= j && s[l] == s[r]) r++;
            r--;

            int cost = dp[l][0] + (k - l) + (r - k);
            if (r < k) cost += dp[k][1];
            else if (l > k) cost += dp[k][0];

            min_cost = (min_cost < cost) ? min_cost : cost;

            l = r; // 跳过已经处理过的字符
        }

        printf("%d\n", min_cost);
    }
}

int main() {
    solve();
    return 0;
}