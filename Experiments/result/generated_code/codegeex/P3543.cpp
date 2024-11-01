#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000010

int a[MAXN], b[MAXN], c[MAXN];

int main() {
    int n, x, y;
    scanf("%d%d%d", &n, &x, &y);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        a[i] -= x; // 先用 x 减去所有数
    }

    for (int i = 1; i <= n; i++) {
        b[i] = a[i] - a[i - 1]; // 计算相邻点的差值
    }

    int cnt = 0, flag = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] > 0) {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        printf("-1\n");
        return 0;
    }

    flag = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] < 0) {
            flag = 1;
            break;
        }
    }

    if (!flag) {
        printf("-1\n");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (b[i] > 0) {
            c[i] = b[i] / y;
            if (b[i] % y != 0) {
                c[i]++;
            }
        } else {
            c[i] = b[i] / x;
            if (b[i] % x != 0) {
                c[i]--;
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i == 1) {
            ans += c[i];
        } else {
            if (c[i] >= c[i - 1]) {
                ans += c[i] - c[i - 1];
            } else {
                ans += c[i];
                c[i + 1] += c[i - 1] - c[i];
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}