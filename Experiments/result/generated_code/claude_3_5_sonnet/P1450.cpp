#include <stdio.h>
#include <string.h>

#define MAX_S 100001

long long dp[MAX_S];
int c[4], d[4];

void init_dp() {
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
}

long long solve(int s) {
    init_dp();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= s; j++) {
            for (int k = 1; k <= d[i] && j + k * c[i] <= s; k++) {
                dp[j + k * c[i]] += dp[j];
            }
        }
    }
    return dp[s];
}

int main() {
    int n, s;
    scanf("%d %d %d %d %d", &c[0], &c[1], &c[2], &c[3], &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d %d", &d[0], &d[1], &d[2], &d[3], &s);
        printf("%lld\n", solve(s));
    }
    
    return 0;
}