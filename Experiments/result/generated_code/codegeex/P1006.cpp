#include <stdio.h>
#include <limits.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    int a[51][51];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    int f[51][51][51][51];
    for (int i1 = 1; i1 <= m; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = 1; i2 <= m; i2++) {
                for (int j2 = 1; j2 <= n; j2++) {
                    f[i1][j1][i2][j2] = INT_MIN;
                }
            }
        }
    }
    
    f[1][1][m][n] = a[1][1] + a[m][n];
    
    for (int i1 = 1; i1 <= m; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = m; i2 >= 1; i2--) {
                for (int j2 = n; j2 >= 1; j2--) {
                    if (i1 == i2 && j1 == j2) continue;
                    if (i1 == i2) {
                        f[i1][j1][i2][j2] = f[i1][j1][i2][j2 + 1] + a[i2][j2];
                        f[i1][j1][i2][j2] = fmax(f[i1][j1][i2][j2], f[i1][j1][i2][j2 - 1] + a[i2][j2]);
                    } else if (j1 == j2) {
                        f[i1][j1][i2][j2] = f[i1][j1][i2 + 1][j2] + a[i2][j2];
                        f[i1][j1][i2][j2] = fmax(f[i1][j1][i2][j2], f[i1][j1][i2 - 1][j2] + a[i2][j2]);
                    } else {
                        f[i1][j1][i2][j2] = f[i1][j1][i2 + 1][j2] + a[i2][j2];
                        f[i1][j1][i2][j2] = fmax(f[i1][j1][i2][j2], f[i1][j1][i2 - 1][j2] + a[i2][j2]);
                        f[i1][j1][i2][j2] = fmax(f[i1][j1][i2][j2], f[i1][j1][i2][j2 + 1] + a[i2][j2]);
                        f[i1][j1][i2][j2] = fmax(f[i1][j1][i2][j2], f[i1][j1][i2][j2 - 1] + a[i2][j2]);
                    }
                    f[i2][j2][i1][j1] = f[i1][j1][i2][j2];
                }
            }
        }
    }
    
    int max = INT_MIN;
    for (int i1 = 1; i1 <= m; i1++) {
        for (int j1 = 1; j1 <= n; j1++) {
            for (int i2 = m; i2 >= 1; i2--) {
                for (int j2 = n; j2 >= 1; j2--) {
                    if (i1 == 1 && j1 == 1 && i2 == m && j2 == n) continue;
                    max = fmax(max, f[i1][j1][i2][j2]);
                }
            }
        }
    }
    
    printf("%d\n", max);
    return 0;
}