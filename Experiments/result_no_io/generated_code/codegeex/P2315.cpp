#include <stdio.h>
#include <string.h>

#define MAXN 110
#define MAXM 10010

int n, m;
int f[MAXN][MAXN][MAXN];
int a[MAXM];

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &a[i]);
    }
    memset(f, 0, sizeof(f));
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        for (int j = i; j <= m; j++) {
            int h = a[j] - a[i] + 1;
            if (h <= n) {
                ans += f[h][j][i - 1] + f[h][i - 1][j];
                f[h][j][i - 1]++;
                f[h][i - 1][j]++;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}