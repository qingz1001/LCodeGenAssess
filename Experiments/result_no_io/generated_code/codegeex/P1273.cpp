#include <stdio.h>
#include <string.h>

#define N 3001

int n, m, k;
int a[N][N], c[N][N], d[N], f[N][N];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n - m; i++) {
        scanf("%d", &k);
        for (int j = 1; j <= k; j++) {
            scanf("%d%d", &a[i][j], &c[i][j]);
        }
    }
    for (int i = n - m + 1; i <= n; i++) {
        scanf("%d", &d[i]);
    }

    for (int i = n - m + 1; i <= n; i++) {
        f[i][0] = 0;
        f[i][1] = d[i];
    }

    for (int i = n - m; i >= 1; i--) {
        for (int j = 0; j <= m; j++) {
            f[i][j] = f[a[i][1]][j];
            for (int k = 2; k <= n - m; k++) {
                f[i][j] = (f[i][j] > f[a[i][k]][j] + c[i][k]) ? f[i][j] : f[a[i][k]][j] + c[i][k];
            }
            for (int k = n - m + 1; k <= n; k++) {
                if (j >= 1 && f[a[i][1]][j - 1] + c[i][k] <= f[i][j]) {
                    f[i][j] = f[a[i][1]][j - 1] + c[i][k];
                }
                for (int l = 2; l <= n - m; l++) {
                    if (j >= 1 && f[a[i][l]][j - 1] + c[i][k] <= f[i][j]) {
                        f[i][j] = f[a[i][l]][j - 1] + c[i][k];
                    }
                }
            }
        }
    }

    int max = 0;
    for (int i = 1; i <= m; i++) {
        max = (f[1][i] > max) ? f[1][i] : max;
    }

    printf("%d", max);
    return 0;
}