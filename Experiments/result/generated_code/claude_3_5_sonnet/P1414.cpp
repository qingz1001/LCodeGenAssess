#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000
#define MAX_INF 1000000

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    int n, abilities[MAX_N];
    int dp[MAX_INF + 1] = {0};
    
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &abilities[i]);
        for (int j = MAX_INF; j >= abilities[i]; j--) {
            if (dp[j] || j == abilities[i]) {
                dp[j] = gcd(dp[j], abilities[i]);
            }
        }
    }
    
    int max_gcd[MAX_N + 1] = {0};
    for (int i = MAX_INF; i >= 1; i--) {
        if (dp[i]) {
            for (int k = n; k >= 1; k--) {
                if (max_gcd[k] == 0 || i > max_gcd[k]) {
                    max_gcd[k] = i;
                }
            }
        }
    }
    
    for (int i = 1; i <= n; i++) {
        printf("%d\n", max_gcd[i]);
    }
    
    return 0;
}