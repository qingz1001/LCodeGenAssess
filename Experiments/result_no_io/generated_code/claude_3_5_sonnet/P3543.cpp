#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000000
#define INF 1000000000

int n, a, b;
int heights[MAX_N];
int dp[MAX_N];

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int abs(int x) {
    return x < 0 ? -x : x;
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    
    int g = gcd(a, b);
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
        if (heights[i] % g != 0) {
            printf("-1\n");
            return 0;
        }
    }
    
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        int h = abs(heights[i]);
        for (int j = 0; j <= h / a; j++) {
            int rem = h - j * a;
            if (rem % b == 0) {
                int ops = j + rem / b;
                if (i == 0 || dp[i-1] != INF) {
                    dp[i] = (i == 0) ? ops : (dp[i] < dp[i-1] + ops ? dp[i] : dp[i-1] + ops);
                }
            }
        }
        if (dp[i] == INF) {
            printf("-1\n");
            return 0;
        }
    }
    
    printf("%d\n", dp[n-1]);
    return 0;
}