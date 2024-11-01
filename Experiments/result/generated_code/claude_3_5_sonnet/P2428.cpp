#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1001
#define MAXM 100001

double a[MAXN][MAXN];
double b[MAXN];
int n, m;

void gauss() {
    for (int i = 1; i <= n; i++) {
        int r = i;
        for (int j = i + 1; j <= n; j++)
            if (abs(a[j][i]) > abs(a[r][i])) r = j;
        if (r != i) {
            for (int j = 1; j <= n; j++) {
                double t = a[i][j];
                a[i][j] = a[r][j];
                a[r][j] = t;
            }
            double t = b[i];
            b[i] = b[r];
            b[r] = t;
        }
        if (a[i][i] == 0) {
            printf("IMPOSSIBLE\n");
            exit(0);
        }
        for (int j = i + 1; j <= n; j++) {
            double f = a[j][i] / a[i][i];
            for (int k = i; k <= n; k++)
                a[j][k] -= f * a[i][k];
            b[j] -= f * b[i];
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = i + 1; j <= n; j++)
            b[i] -= a[i][j] * b[j];
        b[i] /= a[i][i];
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        a[x][x]++;
        a[y][y]++;
        a[x][y]--;
        a[y][x]--;
        b[x] += z;
        b[y] += z;
    }
    for (int i = 1; i <= n; i++)
        a[1][i] = 1;
    b[1] = 0;
    gauss();
    for (int i = 1; i <= n; i++)
        printf("%.2f\n", b[i] / 2);
    return 0;
}