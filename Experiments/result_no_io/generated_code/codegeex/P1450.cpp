#include <stdio.h>
#include <string.h>

long long f[100005];
long long g[100005];
int c[5];
int d[5];

void solve() {
    int i, j, k;
    long long ans;
    scanf("%d%d%d%d%d", &d[1], &d[2], &d[3], &d[4], &k);
    scanf("%d%d%d%d%d", &c[1], &c[2], &c[3], &c[4], &k);
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= d[i]; j++) {
            for (k = c[i]; k <= 100000; k++) {
                f[k] += f[k - c[i]];
            }
        }
    }
    for (i = 1; i <= 100000; i++) {
        g[i] = g[i - 1] + f[i];
    }
    while (k--) {
        ans = 0;
        scanf("%d", &k);
        for (i = 1; i <= 4; i++) {
            for (j = d[i]; j >= 1; j--) {
                ans += g[k - j * c[i]];
            }
        }
        printf("%lld\n", ans);
    }
}

int main() {
    int i, j, k;
    scanf("%d%d%d%d%d", &c[1], &c[2], &c[3], &c[4], &k);
    for (i = 1; i <= 4; i++) {
        for (j = 1; j <= c[i]; j++) {
            f[j] = 1;
        }
    }
    solve();
    return 0;
}