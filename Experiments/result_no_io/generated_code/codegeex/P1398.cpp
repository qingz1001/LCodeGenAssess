#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 150
#define MAXM 500
#define INF 0x3f3f3f3f

int n, m;
int a[MAXN+5][MAXM+5];
int s[MAXN+5][MAXM+5];

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x < y ? x : y;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
            s[i][j] = s[i-1][j] + a[i][j];
        }
    }

    int ans = -INF;
    for (int j = 12; j <= m; j++) {
        int mx[MAXN+5] = {0}, mn[MAXN+5] = {0};
        for (int i = 1; i <= n; i++) {
            mx[i] = max(mx[i-1], s[i][j] - s[i-1][j-11]);
        }
        for (int i = n; i >= 1; i--) {
            mn[i] = min(mn[i+1], s[n][j] - s[i][j-11]);
        }
        for (int i = 1; i <= n; i++) {
            for (int l = i, r = i + 1; r <= n; r++) {
                if (mn[r+1] <= s[n][j] - s[i-1][j-11]) {
                    l++;
                    while (l <= r && s[l][j] - s[l-1][j-11] < mx[l-1]) l++;
                    if (l <= r) {
                        int tmp = s[i-1][j-11] - s[i-1][j] + s[l][j] - s[l-1][j-11];
                        ans = max(ans, tmp);
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}