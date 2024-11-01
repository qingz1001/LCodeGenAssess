#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005
#define MAXM 2000005

int n, m;
int a[MAXN];
int dp[MAXN][21];
int pre[MAXN], suf[MAXN];
int dis[MAXM];

int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    qsort(a, n + 1, sizeof(int), cmp);

    for (int i = 1; i <= n; i++) {
        dp[i][0] = a[i] - a[(i + 1) / 2];
    }

    for (int j = 1; j <= 20; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1 << j) - 1 <= n) {
                dp[i][j] = dp[i][j - 1] + dp[i + (1 << (j - 1))][j - 1];
            } else {
                dp[i][j] = dp[i][j - 1];
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int i = 1; i <= n; i++) {
        pre[i] = dp[1][20] - dp[i][20];
        suf[i] = dp[i][20] - dp[n - i + 1][20];
    }

    for (int i = 1; i <= n; i++) {
        int k = m;
        int l = 1, r = i;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (a[i] - a[mid + 1] >= suf[mid + 1]) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        dis[k] += a[i] - a[l + 1];
        k--;

        l = i, r = n;
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (a[mid] - a[i] <= pre[mid]) {
                l = mid;
            } else {
                r = mid - 1;
            }
        }
        dis[k] += a[l] - a[i];
        k--;

        for (; k > 0; k--) {
            l = 1, r = i;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (a[i] - a[mid + 1] >= suf[mid + 1]) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            dis[k] += a[i] - a[l + 1];
            l = i, r = n;
            while (l < r) {
                int mid = (l + r + 1) >> 1;
                if (a[mid] - a[i] <= pre[mid]) {
                    l = mid;
                } else {
                    r = mid - 1;
                }
            }
            dis[k] += a[l] - a[i];
        }

        for (int j = 1; j <= m; j++) {
            ans = ans < dis[j] ? ans : dis[j];
        }
    }

    printf("%d\n", ans);
    return 0;
}