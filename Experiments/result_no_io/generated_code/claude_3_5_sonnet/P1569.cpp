#include <stdio.h>
#include <string.h>

#define MAX_N 1000

int n;
long long cows[MAX_N];
int dp[MAX_N];

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld", &cows[i]);
    }
    
    memset(dp, 0, sizeof(dp));
    
    long long sum = 0;
    int max_groups = 0;
    
    for (int i = 0; i < n; i++) {
        sum += cows[i];
        if (sum >= 0) {
            dp[i] = (i > 0 ? dp[i-1] : 0) + 1;
        } else {
            dp[i] = (i > 0 ? dp[i-1] : 0);
        }
        
        if (dp[i] > max_groups) {
            max_groups = dp[i];
        }
        
        if (sum < 0) {
            sum = 0;
        }
    }
    
    if (max_groups > 0) {
        printf("%d\n", max_groups);
    } else {
        printf("Impossible\n");
    }
    
    return 0;
}