#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define MAX_M (MAX_N * (MAX_N + 1) / 2)

int n, m;
int a[MAX_N + 1][MAX_N + 1];
int f[MAX_N + 1][MAX_M + 1];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = f[i][j - 1];
            for (int k = 1; k <= i && k <= j; k++) {
                f[i][j] = (f[i][j] > f[i - 1][j - k] + a[i][k]) ? f[i][j] : f[i - 1][j - k] + a[i][k];
            }
        }
    }

    printf("%d\n", f[n][m]);
    return 0;
}