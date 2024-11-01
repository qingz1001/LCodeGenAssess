#include <stdio.h>

#define MAX_M 11
#define MAX_N 21

long long dp[MAX_M][MAX_N];

long long combination(int n, int k) {
    if (k > n - k) k = n - k;
    long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

    long long total_steps = m + n - 2;
    long long right_steps = n - 1;
    long long routes = combination(total_steps, right_steps);

    printf("%lld\n", routes);

    return 0;
}