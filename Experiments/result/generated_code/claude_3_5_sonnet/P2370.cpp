#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1000
#define MAX_S 1000
#define MAX_V 1000000

int n, p, S;
int W[MAX_N + 1], V[MAX_N + 1];
int dp[MAX_S + 1][MAX_V + 1];

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &W[i], &V[i]);
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = S; j >= W[i]; j--) {
            for (int k = MAX_V; k >= V[i]; k--) {
                dp[j][k] = min(dp[j][k], max(dp[j - W[i]][k - V[i]], W[i]));
            }
        }
    }

    int ans = 0x3f3f3f3f;
    for (int j = 0; j <= S; j++) {
        for (int k = p; k <= MAX_V; k++) {
            ans = min(ans, dp[j][k]);
        }
    }

    if (ans == 0x3f3f3f3f) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", ans);
    }

    return 0;
}