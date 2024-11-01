#include <stdio.h>
#include <stdlib.h>

#define MAX_V 20000
#define MAX_N 30

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int V, n;
    int volumes[MAX_N];
    int dp[MAX_V + 1];

    scanf("%d", &V);
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &volumes[i]);
    }

    for (int i = 0; i <= V; i++) {
        dp[i] = V;
    }

    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = V; j >= volumes[i]; j--) {
            dp[j] = min(dp[j], dp[j - volumes[i]] + volumes[i]);
        }
    }

    int min_remaining_space = V;
    for (int i = 0; i <= V; i++) {
        min_remaining_space = min(min_remaining_space, V - dp[i]);
    }

    printf("%d\n", min_remaining_space);

    return 0;
}