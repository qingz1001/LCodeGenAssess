#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 8000
#define MAXK 1000000000
#define MAXP 3000

int n, k, p;
int h[MAXN + 1];
double dp[MAXN + 1][MAXK + 1];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &k, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }

    qsort(h + 1, n, sizeof(int), compare);

    for (int i = 1; i <= n; i++) {
        dp[i][0] = h[1];
    }

    for (int j = 1; j <= k; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = dp[i][j - 1];
            for (int l = 1; l < i; l++) {
                dp[i][j] = max(dp[i][j], (dp[l][j - 1] * l + h[i]) / (l + 1));
            }
        }
    }

    printf("%.6f\n", dp[n][k]);

    return 0;
}