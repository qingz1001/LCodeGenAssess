#include <stdio.h>
#include <string.h>

int n, m;
int a[1005][1005], b[1005][1005], c[1005][1005], d[1005][1005];
int ans;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // 计算左上到右下的对角线
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            b[i][j] = (a[i][j] == a[i - 1][j - 1]) ? b[i - 1][j - 1] + 1 : 1;
        }
    }

    // 计算右上到左下的对角线
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) {
            c[i][j] = (a[i][j] == a[i - 1][j + 1]) ? c[i - 1][j + 1] + 1 : 1;
        }
    }

    // 计算左右对称的正方形
    for (int k = 1; k <= n + m - 1; k++) {
        for (int i = 1; i <= n; i++) {
            int j = k - i + 1;
            if (j < 1 || j > m) continue;
            d[i][j] = (a[i][j] == a[i][m - j + 1]) ? d[i][j - 1] + 1 : 1;
        }
    }

    // 计算上下对称的正方形
    for (int k = 1; k <= n + m - 1; k++) {
        for (int j = 1; j <= m; j++) {
            int i = k - j + 1;
            if (i < 1 || i > n) continue;
            int t = d[i][j];
            if (t > 0) {
                for (int l = 1; l <= t; l++) {
                    if (b[i + l][j + l] >= l && c[i + l][j - l + 1] >= l) {
                        ans++;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}