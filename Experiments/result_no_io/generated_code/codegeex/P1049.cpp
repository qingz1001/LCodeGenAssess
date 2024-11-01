#include <stdio.h>
#include <string.h>

int main() {
    int V, n;
    scanf("%d%d", &V, &n);
    int volumes[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &volumes[i]);
    }

    int dp[V + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++) {
        for (int j = V; j >= volumes[i]; j--) {
            dp[j] = (dp[j] > dp[j - volumes[i]] + volumes[i]) ? dp[j] : dp[j - volumes[i]] + volumes[i];
        }
    }

    printf("%d\n", V - dp[V]);
    return 0;
}