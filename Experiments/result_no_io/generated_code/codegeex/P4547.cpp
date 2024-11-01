#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXN 16

int n, m;
int f[MAXN][MAXN];
int g[MAXN][MAXN];
int h[MAXN][MAXN];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int t, a1, b1, a2, b2;
        scanf("%d%d%d", &t, &a1, &b1);
        a1--; b1--; // Convert to 0-based index
        if (t == 0) {
            f[a1][b1] = 1;
        } else if (t == 1) {
            scanf("%d%d", &a2, &b2);
            a2--; b2--; // Convert to 0-based index
            g[a1][b1] = g[a2][b2] = 1;
        } else if (t == 2) {
            scanf("%d%d", &a2, &b2);
            a2--; b2--; // Convert to 0-based index
            h[a1][b1] = h[a2][b2] = 1;
        }
    }

    int ans = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int sum = 0;
            for (int k = 0; k < n; k++) {
                if (i != k) {
                    sum = (sum + f[i][k] * f[j][k]) % MOD;
                }
            }
            for (int k = 0; k < n; k++) {
                if (i != k && j != k) {
                    sum = (sum + g[i][k] * f[j][k] + g[j][k] * f[i][k]) % MOD;
                }
            }
            for (int k = 0; k < n; k++) {
                if (i != k && j != k) {
                    sum = (sum + h[i][k] * h[j][k]) % MOD;
                }
            }
            ans = 1LL * ans * (1 + sum) % MOD;
        }
    }

    printf("%d\n", ans);
    return 0;
}