#include <stdio.h>
#include <math.h>

#define MAX_N 100005

int n, k;
double dp[MAX_N];

double max(double a, double b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d", &n, &k);
    
    for (int i = 1; i <= n; i++) {
        dp[i] = 1.0 / i;
    }
    
    for (int i = 2; i <= k; i++) {
        for (int j = n; j >= i; j--) {
            double sum = 0;
            for (int m = 1; m <= j - 1; m++) {
                sum += dp[j - m];
            }
            dp[j] = max(dp[j], (double)1 / j + sum / (j - 1));
        }
    }
    
    printf("%.9f\n", dp[n]);
    
    return 0;
}