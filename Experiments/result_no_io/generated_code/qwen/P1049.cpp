#include <stdio.h>
#include <stdlib.h>

#define MAXN 35
#define MAXV 20001

int main() {
    int V, n;
    scanf("%d %d", &V, &n);
    int volumes[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &volumes[i]);
    }

    int dp[MAXV];
    for (int i = 0; i <= V; ++i) {
        dp[i] = i;
    }

    for (int i = 0; i < n; ++i) {
        for (int j = V; j >= volumes[i]; --j) {
            dp[j] = dp[j] < dp[j - volumes[i]] + volumes[i] ? dp[j] : dp[j - volumes[i]] + volumes[i];
        }
    }

    printf("%d\n", V - dp[V]);

    return 0;
}