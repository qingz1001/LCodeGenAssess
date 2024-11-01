#include <stdio.h>
#include <string.h>

#define N 500
#define M 2500
#define P 100000000

int n, p, a[N], f[2][M][M], g[M], ans;

int main() {
    int i, j, k, x, y, o, b[M];
    scanf("%d%d", &n, &p);
    for (i = 1; i < n; i++) scanf("%d", &a[i]);
    memset(b, -1, sizeof(b));
    for (i = 1; i < n; i++) {
        x = 0;
        for (j = 2; j * j <= a[i]; j++) if (a[i] % j == 0) {
            x |= 1 << (j - 1);
            while (a[i] % j == 0) a[i] /= j;
        }
        if (a[i] > 1) x |= 1 << (a[i] - 1);
        b[x] = i;
    }
    for (i = 0; i < M; i++) if (b[i] >= 0) for (j = 0; j < M; j++) if (b[j] >= 0 && (i & j) == 0)
        for (k = 0; k < M; k++) if (b[k] >= 0 && (i & k) == 0 && (j & k) == 0) {
            o = 1;
            for (j = 1; j < 15; j++) if ((i >> (j - 1)) & 1) for (k = 1; k < 15; k++) if (((j ^ k) >> (j - 1)) & 1 && ((j ^ k) >> (k - 1)) & 1) {
                if ((j ^ k) & i) o = 0;
                if ((j ^ k) & j) o = 0;
                if ((j ^ k) & k) o = 0;
            }
            if (o) g[i | j | k] = (g[i | j | k] + b[i] + b[j] + b[k]) % P;
        }
    memset(f, 0, sizeof(f));
    f[0][0][0] = 1;
    for (i = 0; i < M; i++) if (b[i] >= 0) for (j = 0; j < M; j++) if (f[o ^ 1][j][0]) for (k = 0; k < M; k++) if ((i & j) == 0 && (i & k) == 0 && (j & k) == 0)
        f[o][j | i][k] = (f[o][j | i][k] + f[o ^ 1][j][0] + g[i | j | k]) % P;
    for (i = 0; i < M; i++) ans = (ans + f[o][i][i]) % P;
    printf("%d\n", ans);
    return 0;
}