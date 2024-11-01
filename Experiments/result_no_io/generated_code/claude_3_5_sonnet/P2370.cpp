#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1005
#define MAX_S 1005

int n, p, S;
int W[MAX_N], V[MAX_N];
int dp[MAX_S];

int max(int a, int b) {
    return a > b ? a : b;
}

int solve() {
    int maxW = 0;
    for (int i = 1; i <= n; i++) {
        maxW = max(maxW, W[i]);
        for (int j = S; j >= W[i]; j--) {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }
    
    if (dp[S] < p) {
        return -1;
    }
    
    int left = 1, right = maxW;
    while (left < right) {
        int mid = (left + right) / 2;
        memset(dp, 0, sizeof(dp));
        
        for (int i = 1; i <= n; i++) {
            if (W[i] <= mid) {
                for (int j = S; j >= W[i]; j--) {
                    dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
                }
            }
        }
        
        if (dp[S] >= p) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &W[i], &V[i]);
    }
    
    int result = solve();
    if (result == -1) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", result);
    }
    
    return 0;
}