#include <stdio.h>
#include <string.h>
#include <algorithm>
#define N 75
#define M 400005
using namespace std;

int n, K, a[N], w[N], f[N][N][N];
long long g[N][N][N];

struct node {
    int x, y, z;
} b[N];

bool cmp(node a, node b) {
    return a.x < b.x;
}

int main() {
    int i, j, k, l, x, y, z, ans = M;
    scanf("%d%d", &n, &K);
    for (i = 1; i <= n; i++)
        scanf("%d", &b[i].x);
    for (i = 1; i <= n; i++)
        scanf("%d", &b[i].y);
    for (i = 1; i <= n; i++)
        scanf("%d", &b[i].z);

    sort(b + 1, b + n + 1, cmp);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            for (k = 1; k <= n; k++) {
                f[i][j][k] = M;
                g[i][j][k] = 0;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        f[i][i][i] = w[i] = b[i].y;
        g[i][i][i] = b[i].z;
    }

    for (l = 2; l <= n; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            for (k = i; k <= j; k++) {
                x = f[i][k - 1][w[k]] + f[k + 1][j][w[k]] + K;
                y = g[i][k - 1][w[k]] + g[k + 1][j][w[k]] + b[k].z;
                for (z = i; z <= j; z++) {
                    if (x < f[i][j][z]) {
                        f[i][j][z] = x;
                        g[i][j][z] = y;
                    }
                }
            }
            for (z = i; z <= j; z++) {
                x = f[i][j][z];
                y = g[i][j][z];
                for (k = i; k <= j; k++) {
                    if (w[k] < w[z]) {
                        x = min(x, f[i][k][w[z]] + f[k + 1][j][z]);
                        y = min(y, g[i][k][w[z]] + g[k + 1][j][z]);
                    }
                }
                for (k = i; k <= j; k++) {
                    if (w[k] > w[z]) {
                        x = min(x, f[i][k][z] + f[k + 1][j][w[z]]);
                        y = min(y, g[i][k][z] + g[k + 1][j][w[z]]);
                    }
                }
                f[i][j][w[z]] = x;
                g[i][j][w[z]] = y;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        if (f[1][n][i] < ans)
            ans = f[1][n][i];
    }

    printf("%d\n", ans);
    return 0;
}