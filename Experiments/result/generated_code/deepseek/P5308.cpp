#include <stdio.h>
#include <math.h>

double dp[100005];

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        dp[i] = log(i);
    }

    for (int i = 1; i < k; i++) {
        for (int j = n; j >= 1; j--) {
            for (int x = 1; x <= j; x++) {
                dp[j] = max(dp[j], dp[j - x] + log(x) - log(j));
            }
        }
    }

    double result = dp[n];
    result = exp(result);

    printf("%.9f\n", result);

    return 0;
}