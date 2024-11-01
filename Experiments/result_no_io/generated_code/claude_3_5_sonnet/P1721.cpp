#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_N 8000
#define MAX_P 3000

typedef long long ll;

int n, k, p;
int h[MAX_N + 1];
double dp[MAX_N + 1][MAX_N + 1];

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

double calc(int l, int r) {
    double sum = 0;
    for (int i = l; i <= r; i++) {
        sum += h[i];
    }
    return sum / (r - l + 1);
}

double solve() {
    qsort(h + 1, n, sizeof(int), cmp);
    
    for (int i = 1; i <= n; i++) {
        dp[1][i] = calc(1, i);
    }
    
    for (int i = 2; i <= k + 1 && i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[i][j] = dp[i-1][j];
            for (int t = i - 1; t < j; t++) {
                double tmp = calc(t + 1, j);
                if (tmp > dp[i-1][t]) {
                    dp[i][j] = fmax(dp[i][j], fmin(dp[i-1][t], tmp));
                }
            }
        }
    }
    
    return dp[fmin(k + 1, n)][n];
}

int main() {
    scanf("%d%d%d", &n, &k, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    
    double ans = solve();
    printf("%.*f\n", p, ans);
    
    return 0;
}