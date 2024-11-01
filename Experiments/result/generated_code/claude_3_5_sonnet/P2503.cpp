#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_N 20
#define MAX_M 6

int n, m;
int a[MAX_N];
double dp[1 << MAX_N][MAX_M + 1];
int sum[1 << MAX_N];

int count_bits(int x) {
    int count = 0;
    while (x) {
        count += x & 1;
        x >>= 1;
    }
    return count;
}

double solve() {
    int all = (1 << n) - 1;
    for (int i = 0; i <= all; i++) {
        sum[i] = 0;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                sum[i] += a[j];
            }
        }
    }

    for (int i = 0; i <= all; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = DBL_MAX;
        }
    }

    dp[0][0] = 0;
    for (int i = 1; i <= all; i++) {
        for (int j = 1; j <= m && j <= count_bits(i); j++) {
            for (int k = i; k > 0; k = (k - 1) & i) {
                double avg = (double)sum[all] / m;
                double diff = sum[k] - avg;
                double new_variance = dp[i - k][j - 1] + diff * diff / m;
                if (new_variance < dp[i][j]) {
                    dp[i][j] = new_variance;
                }
            }
        }
    }

    return sqrt(dp[all][m]);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    double result = solve();
    printf("%.2f\n", result);

    return 0;
}