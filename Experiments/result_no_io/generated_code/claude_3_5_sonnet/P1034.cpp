#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 51
#define MAX_K 5
#define INF 0x3f3f3f3f

int n, k;
int x[MAX_N], y[MAX_N];
int dp[MAX_N][MAX_K];

int min(int a, int b) {
    return a < b ? a : b;
}

int area(int l, int r) {
    int minx = INF, miny = INF;
    int maxx = -INF, maxy = -INF;
    for (int i = l; i <= r; i++) {
        minx = min(minx, x[i]);
        miny = min(miny, y[i]);
        maxx = x[i] > maxx ? x[i] : maxx;
        maxy = y[i] > maxy ? y[i] : maxy;
    }
    return (maxx - minx) * (maxy - miny);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        dp[i][1] = area(1, i);
    }

    for (int j = 2; j <= k; j++) {
        for (int i = j; i <= n; i++) {
            for (int m = j - 1; m < i; m++) {
                dp[i][j] = min(dp[i][j], dp[m][j-1] + area(m+1, i));
            }
        }
    }

    printf("%d\n", dp[n][k]);
    return 0;
}