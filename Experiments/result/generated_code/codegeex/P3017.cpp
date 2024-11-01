#include <stdio.h>
#include <stdlib.h>

#define MAXN 505

int n, m, a, b;
int sum[MAXN][MAXN];
int s[MAXN][MAXN];

int main() {
    int i, j, k, ans = 0;
    scanf("%d%d%d%d", &n, &m, &a, &b);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            scanf("%d", &sum[i][j]);
            s[i][j] = s[i][j-1] + sum[i][j];
        }
    }

    for (i = 1; i <= n - a + 1; i++) {
        int min = 0x7fffffff;
        for (j = i + a - 1; j <= n; j++) {
            for (k = 1; k <= m - b + 1; k++) {
                int max = 0;
                for (int l = k; l <= m; l += b) {
                    int temp = 0;
                    for (int p = i; p <= j; p++) {
                        temp += s[p][l] - s[p][l-b];
                    }
                    if (temp > max) max = temp;
                }
                if (max < min) min = max;
            }
            if (min > ans) ans = min;
        }
    }

    printf("%d", ans);
    return 0;
}