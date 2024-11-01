#include <stdio.h>
#include <stdlib.h>

#define MAXN 4001

int n, c, q, len[MAXN], num[MAXN], a[MAXN], f[MAXN], g[MAXN];

int main() {
    int t;
    scanf("%d", &t);
    for (int k = 1; k <= t; k++) {
        scanf("%d%d%d", &n, &c, &q);
        for (int i = 1; i <= c; i++) {
            scanf("%d%d", &len[i], &num[i]);
        }
        for (int i = 1; i <= q; i++) {
            scanf("%d", &a[i]);
        }

        // 预处理f和g数组
        for (int i = 1; i <= c; i++) {
            int max_len = len[i] * num[i];
            for (int j = 1; j <= n; j++) {
                f[j] = g[j] = 0;
                for (int k = 1; k <= j; k++) {
                    if (j - k >= max_len) {
                        f[j] = f[j] > f[k - 1] + len[i] ? f[j] : f[k - 1] + len[i];
                    } else {
                        f[j] = f[j] > f[k - 1] ? f[j] : f[k - 1];
                    }
                }
                for (int k = j; k <= n; k++) {
                    if (k - j >= max_len) {
                        g[k] = g[k] > g[k - 1] + len[i] ? g[k] : g[k - 1] + len[i];
                    } else {
                        g[k] = g[k] > g[k - 1] ? g[k] : g[k - 1];
                    }
                }
            }
        }

        // 判断是否有可能合法放置所有战舰
        int flag = 0;
        for (int i = 1; i <= n; i++) {
            if (f[i] + g[n - i + 1] >= n) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            printf("0\n");
            continue;
        }

        // 判断最早在第几次询问后可以断定 GD 说了谎
        flag = 0;
        for (int i = 1; i <= q; i++) {
            if (a[i] <= n / 2) {
                if (f[a[i]] >= a[i]) {
                    flag = 1;
                    break;
                }
            } else {
                if (g[n - a[i] + 1] >= n - a[i] + 1) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            printf("%d\n", i);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}